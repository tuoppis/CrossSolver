#include "exsolver.h"

exsolver::exsolver(QObject *parent) :
    QObject(parent)
{
}

exsolver::exsolver(int rows, int cols, const WordList &words):
    _state(rows, cols),
    _row_words(words.get( [=] (const QString& var) { return var.length() == cols; } )),
    _col_words((cols == rows) ? _row_words: words.get( [=] (const QString& var) { return var.length() == rows; })),
    _total(1),
    _progress(0),
    _id(0),
    _step(1),
    _exit_on_first(false)
{

}

exsolver::exsolver(const exsolver &solv, int id, int step):
    _state(solv._state),
    _row_words(solv._row_words),
    _col_words(solv._col_words),
    _total(1),
    _progress(0),
    _id(qMax(0, id)),
    _step(qMax(id + 1, step)),
    _exit_on_first(false)
{

}

bool exsolver::RW_first(int row_idx, const QString &row_word, const WordList::Span &COL_SPAN)
{
    strToRow(row_idx, 0, row_word);

    QString store(qMax(_state.cols(), _state.rows()), '\0');

    if (row_idx == 0) {
        for (int i = COL_SPAN.start + _id; i < COL_SPAN.end; i += _step) {
            increaseProg(_step);
            strToCol(1, 0, _col_words[i]);
            if (Row(1, 1, store)) return true;
        }
    } else {
        QChar cmp = row_word[0];

        for (int i = COL_SPAN.start + _id; i < COL_SPAN.end; i += _step) {
            increaseProg(_step);
            const QString& cw = _col_words[i];
            if (cmp != cw[row_idx]) continue;
            strToCol(0, 0, cw);
            if (RW_Row(0, 1, row_idx, row_word, store)) return true;
        }
    }
    return false;
}

bool exsolver::RW_Col(int row, int col, int row_idx, const QString &row_word, QString& store)
{
    if (row >= _state.rows()) return testSolutionAt(row, col, store);

    if (row == row_idx) { // skipping set row
        if (row == (_state.rows() - 1)) return testSolutionAt(row + 1, col, store);

        store.resize(row + 1);
        auto skip = spanFromCol(col, store);

        for (int i = skip.start; i < skip.end; i++) {
            strToCol(row, col, _col_words[i]);
            if (Row(row + 1, col + 1, store)) return true;
        }
    } else {
        QChar cmp = row_word[col];

        store.resize(row);
        auto span = spanFromCol(col, store);

        for (int i = span.start; i < span.end; i++) {
            const QString& cw = _col_words[i];
            if (cmp != cw[row_idx]) continue;
            strToCol(row, col, cw);
            if (RW_Row(row, col + 1, row_idx, row_word, store)) return true;
        }
    }
    return false;
}

bool exsolver::RW_Row(int row, int col, int row_idx, const QString &row_word, QString& store)
{
    if (col >= _state.cols()) return testSolutionAt(row, col, store);

    store.resize(col);
    auto span = spanFromRow(row, store);

    for (int i = span.start; i < span.end; i++) {
        strToRow(row, col, _row_words[i]);
        if (RW_Col(row + 1, col, row_idx, row_word, store)) return true;
    }
    return false;
}

bool exsolver::CW_first(int col_idx, const QString &col_word, const WordList::Span &ROW_SPAN)
{
    strToCol(0, col_idx, col_word);

    QString store(qMax(_state.cols(), _state.rows()), '\0');

    if (col_idx == 0) {
        for (int i = ROW_SPAN.start + _id; i < ROW_SPAN.end; i += _step) {
            increaseProg(_step);
            strToRow(0, 1, _row_words[i]);
            if (Col(1, 1, store)) return true;
        }
    } else {
        QChar cmp = col_word[0];

        for (int i = ROW_SPAN.start + _id; i < ROW_SPAN.end; i += _step) {
            increaseProg(_step);
            const QString& rw = _row_words[i];
            if (rw[col_idx] != cmp) continue;
            strToRow(0, 1, rw);
            if (CW_Col(0, 1, col_idx, col_word, store)) return true;
        }
    }
    return false;
}

bool exsolver::CW_Col(int row, int col, int col_idx, const QString &col_word, QString &store)
{
    if (row >= _state.rows()) return testSolutionAt(row, col, store);

    store.resize(row);
    auto span = spanFromCol(col, store);

    for (int i = span.start; i < span.end; i++) {
        strToCol(row, col, _col_words[i]);
        if (CW_Row(row, col + 1, col_idx, col_word, store)) return true;
    }
    return false;
}

bool exsolver::CW_Row(int row, int col, int col_idx, const QString &col_word, QString &store)
{
    if (col >= _state.cols()) return testSolutionAt(row, col, store);

    if (col == col_idx) { // skip set column
        if (col == (_state.cols() - 1)) return testSolutionAt(row, col, store);

        store.resize(col + 1);
        auto skip = spanFromRow(row, store);
        for (int i = skip.start; i < skip.end; i++) {
            strToRow(row, col, _row_words[i]);
            if (Row(row + 1, col + 1, store)) return true;
        }
    } else {
        QChar cmp = col_word[row];

        store.resize(col);
        auto span = spanFromRow(row, store);
        for (int i = span.start; span.end; i++) {
            const QString& rw = _row_words[i];
            if (cmp != rw[col_idx]) continue;
            strToRow(row, col, rw);
            if (CW_Col(row + 1, col, col_idx, col_word, store)) return true;
        }
    }
    return false;
}

bool exsolver::Col(int row, int col, QString &store)
{
    if (row >= _state.rows()) return testSolutionAt(row, col, store);
    store.resize(row);
    auto span = spanFromCol(col, store);
    for (int i = span.start; i < span.end; i++) {
        strToCol(row, col, _col_words[i]);
        if (Row(row, col + 1, store)) return true;
    }
    return false;
}

bool exsolver::Row(int row, int col, QString &store)
{
    if (col >= _state.cols()) return testSolutionAt(row, col, store);
    store.resize(col);
    auto span = spanFromRow(row, store);
    for (int i = span.start; i < span.end; i++) {
        strToRow(row, col, _row_words[i]);
        if (Col(row + 1, col, store)) return true;
    }
    return false;
}

const WordList::Span exsolver::spanFromCol(int col, QString &str)
{
    for (int c = col + 1; c < _state.cols(); c++) {
        colToStr(c, str);
        if (_col_words.countStartWith(str) <= 0) return WordList::Span();
    }
    colToStr(col, str);
    return _col_words.spanStartingWith(str);
}

const WordList::Span exsolver::spanFromRow(int row, QString &str)
{
    for (int r = row + 1; r < _state.rows(); r++) {
        rowToStr(r, str);
        if (_row_words.countStartWith(str) <= 0) return WordList::Span();
    }
    rowToStr(row, str);
    return _row_words.spanStartingWith(str);
}

void exsolver::increaseProg(int amount)
{
    int pc = _inv * (_progress += amount); //(100 * (_progress += amount)) / _total;

    if (pc != _percent) {
        _percent = pc;
        emit progressChanged(_id, _percent);
    }

}

bool exsolver::testSolutionAt(int row, int col, QString& store)
{
    int rows = _state.rows(), cols = _state.cols();

    store.resize(cols);
    for (int r = row; r < rows; r++) {
        rowToStr(r, store);
        if (!_row_words.hasWord(store)) return false;
    }
    store.resize(rows);
    for (int c = col; c < cols; c++) {
        colToStr(c, store);
        if (!_col_words.hasWord(store)) return false;
    }

    for (int i = 1; i < _needed.length(); i++) {
        const QString& w = _needed[i];
        if (w.length() == cols) {
            store.resize(cols);
            for (int r = 0; r < rows; r++) {
                rowToStr(r, store);
                if (w == store) goto bypass;
            }
        }
        if (w.length() == rows) {
            store.resize(rows);
            for (int c = 0; c < cols; c++) {
                colToStr(c, store);
                if (w == store) goto bypass;
            }
        }
        return false;
        bypass:
        continue;
    }
    _solutions.append(_state);
    return _exit_on_first;
}

void exsolver::beginWork(const QStringList &needed)
{
    _solutions.clear();
    if (needed.isEmpty()) { completed(); return; }
    for (auto w: needed) {
        if (!_row_words.hasWord(w) && !_col_words.hasWord(w))
            { completed(); return; }
    }

    _needed = needed;
    _progress = 0;
    _exit_on_first = false;

    const QString& word = _needed[0];
    QString x = word.left(1);

    if (_row_words.hasWord(word)) {
        auto span = _col_words.spanStartingWith(x);
        setTotal( (_state.rows() - 1) * _col_words.length() + span.length() - _id );

        if (RW_first(0, word, span)) { completed(); return; }
        x.resize(0);
        span = _col_words.spanStartingWith(x);
        for (int r = 1; r < _state.rows(); r++)
            if (RW_first(r, word, span)) { completed(); return; }
    } else {
        auto span = _row_words.spanStartingWith(x);
        setTotal( (_state.cols() - 1) * _row_words.length() + span.length() - _id );

        if (CW_first(0, word, span)) return completed();
        x.resize(0);
        span = _row_words.spanStartingWith(x);
        for (int c = 1; c < _state.cols(); c++)
            if (CW_first(c, word, span)) { completed(); return; }
    }
    completed();
}




