#include "solver.h"

Solver::Solver(int rows, int cols, const WordList& words):
    _state(rows, cols),
    _col_words(words.get( [=] (const QString& var) { return var.length() == rows; } )),
    _row_words((cols == rows) ? _col_words: words.get( [=] (const QString& var) { return var.length() == cols; } )),
    _total(1),
    _progress(0),
    _percent(0),
    _id(0),
    _step(1),
    _exit_on_first(false)
{

}

Solver::Solver(const Solver &init, int id, int step):
    _state(init._state),
    _col_words(init._col_words),
    _row_words(init._row_words),
    _total(1),
    _progress(0),
    _id(qMax(0, id)),
    _step(qMax(_id + 1, step)),
    _exit_on_first(false)
{

}


bool Solver::RW_first(int row_idx, const QString &row_word, const WordList& COL_WL)
{
    strToRow(row_idx, 0, row_word);

    QString hold(1, '\0');
    WordList rwl;

    if (row_idx == 0) {
        for (int i = _id; i < COL_WL.length(); i += _step) {
            increaseProg(_step);
            strToCol(1, 0, COL_WL[i]);
            if (wordsFromRow(1, hold, rwl) && Row(1, 1, rwl)) return true;
        }
    } else {
        QChar cmp = row_word[0];

        for (int i = _id; i < COL_WL.length(); i += _step) {
            increaseProg(_step);
            const QString& cw = COL_WL[i];
            if (cw[row_idx] != cmp) continue;
            strToCol(0, 0, cw);
            if (wordsFromRow(0, hold, rwl) && RW_Row(0, 1, row_idx, row_word, rwl)) return true;
        }
    }
    return false;
}

bool Solver::RW_Col(int row, int col, int row_idx, const QString& row_word, const WordList& COL_WL)
{
    if (row >= _state.rows()) {
        return testSolutionAt(row, col + 1);
    }

    QString hold(col + 1, '\0');
    WordList rowlist;

    if (row_idx == row) {
        if (row == (_state.rows() - 1)) {
            return testSolutionAt(row, col);
        }

        for (auto cw: COL_WL) {
            strToCol(row, col, cw);
            if (wordsFromRow(row + 1, hold, rowlist) && Row(row + 1, col + 1, rowlist)) return true;
        }
    } else {
        QChar cmp = row_word[col];

        for (auto cw: COL_WL) {
            if (cw[row_idx] != cmp) continue;
            strToCol(row, col, cw);
            if (wordsFromRow(row, hold, rowlist) && RW_Row(row, col + 1, row_idx, row_word, rowlist)) return true;
        }
    }
    return false;
}

bool Solver::RW_Row(int row, int col, int row_idx, const QString &row_word, const WordList& ROW_WL)
{
    if (col >= _state.cols()) {
        return testSolutionAt(row + 1, col);
    }

    QString hold(row + 2, '\0');
    WordList cwl;

    if (row == (row_idx - 1)) {
        colToStr(col, hold);

        for (auto rw: ROW_WL) {
            strToRow(row, col, rw);
            hold[row] = rw[col];
            if (cwl.selectStartWith(hold, _col_words) && RW_Col(row + 1, col, row_idx, row_word, cwl))
                return true;
        }
    } else {
        hold.resize(row + 1);
        for (auto rw: ROW_WL) {
            strToRow(row, col, rw);
            if (wordsFromCol(col, hold, cwl) && RW_Col(row + 1, col, row_idx, row_word, cwl)) return true;
        }
    }
    return false;
}

bool Solver::CW_first(int col_idx, const QString &col_word, const WordList &ROW_WL)
{
    strToCol(0, col_idx, col_word);

    WordList cwl;
    QString hold(1, '\0');

    if (col_idx == 0) {
        for (int i = _id; i < ROW_WL.length(); i += _step) {
            increaseProg(_step);
            strToRow(0, 1, ROW_WL[i]);
            if (wordsFromCol(1, hold, cwl) && Col(1, 1, cwl)) return true;
        }
    } else {
        QChar cmp = col_word[0];
        for (int i = _id; i < ROW_WL.length(); i += _step) {
            increaseProg(_step);
            const QString& rw = ROW_WL[i];
            if (rw[col_idx] != cmp) continue;
            strToRow(0, 1, rw);
            if (wordsFromCol(0, hold, cwl) && CW_Col(0, 1, col_idx, col_word, cwl)) return true;
        }
    }
    return false;
}

bool Solver::CW_Col(int row, int col, int col_idx, const QString& col_word, const WordList &COL_WL)
{
    if (row >= _state.rows()) {
        testSolutionAt(row, col + 1);
    }

    QString hold(col + 2, '\0');
    WordList rwl;

    if (col == (col_idx - 1)) {
        rowToStr(row, hold);

        for (auto cw: COL_WL) {
            strToCol(row, col, cw);
            hold[col] = cw[row];
            rwl.selectStartWith(hold, _row_words);
            if (!rwl.isEmpty() && CW_Row(row, col + 1, col_idx, col_word, rwl)) return true;
        }

    } else {
        hold.resize(col + 1);
        for (auto cw: COL_WL) {
            strToCol(row, col, cw);
            if (wordsFromRow(row, hold, rwl) && CW_Row(row, col + 1, col_idx, col_word, rwl)) return true;
        }
    }
    return false;
}

bool Solver::CW_Row(int row, int col, int col_idx, const QString &col_word, const WordList &ROW_WL)
{
    if (col >= _state.cols()) {
        testSolutionAt(row + 1, col);
    }

    QString hold(row + 1, '\0');
    WordList cwl;

    if (col == col_idx) {
        if (col == (_state.cols() - 1)) {
            testSolutionAt(row, col);
        }

        for (auto rw: ROW_WL) {
            strToRow(row, col, rw);
            if (wordsFromCol(col + 1, hold, cwl) && Row(row + 1, col + 1, cwl)) return true;
        }
    } else {
        QChar cmp = col_word[row];

        for (auto rw: ROW_WL) {
            if (rw[col_idx] != cmp) continue;
            strToRow(row, col, rw);
            if (wordsFromCol(col, hold, cwl) && CW_Col(row + 1, col, col_idx, col_word, cwl)) return true;
        }

    }
    return false;
}

bool Solver::Col(int row, int col, const WordList& COL_WL)
{
    if (row >= _state.rows()) {
        testSolutionAt(row, col + 1);
    }

    QString hold(col + 1, '\0');
    WordList rwl;

    for (auto cw: COL_WL) {
        strToCol(row, col, cw);
        if (wordsFromRow(row, hold, rwl) && Row(row, col + 1, rwl)) return true;
    }
    return false;
}

bool Solver::Row(int row, int col, const WordList &ROW_WL)
{
    if (col >= _state.cols()) {
        testSolutionAt(row + 1, col);
    }

    QString hold(row + 1, '\0');
    WordList cwl;

    for (auto rw: ROW_WL) {
        strToRow(row, col, rw);
        if (wordsFromCol(col, hold, cwl) && Col(row + 1, col, cwl)) return true;
    }
    return false;
}

bool Solver::wordsFromCol(int col, QString &str, WordList &list)
{
    for (int c = col + 1; c < _state.cols(); c++) {
        colToStr(c, str);
        if (_col_words.countStartWith(str) <= 0) return false;
    }
    colToStr(col, str);
    list.selectStartWith(str, _col_words);
    return !list.isEmpty();
}

bool Solver::wordsFromRow(int row, QString &str, WordList &list)
{
    for (int r = row + 1; r < _state.rows(); r++) {
        rowToStr(r, str);
        if (_row_words.countStartWith(str) <= 0) return false;
    }
    rowToStr(row, str);
    list.selectStartWith(str, _row_words);
    return !list.isEmpty();
}

bool Solver::testSolutionAt(int row, int col)
{
    int rows = _state.rows(), cols = _state.cols();
    QString hold(qMax(rows, cols));

    hold.resize(cols);
    for (int r = row; r < rows; r++) {
        rowToStr(r, hold);
        if (!_row_words.hasWord(hold)) return false;
    }
    hold.resize(rows);
    for (int c = col; c < cols; c++) {
        colToStr(c, hold);
        if (!_col_words.hasWord(hold)) return false;
    }

    for (int i = 1; i < _needed.length(); i++) {
        QString& w = _needed[i];
        if (w.length() == cols) {
            hold.resize(cols);
            for (int r = 0; r < rows; r++) {
                rowToStr(r, hold);
                if (w == hold) goto bypass;
            }
        }
        if (w.length() == rows) {
            hold.resize(rows);
            for (int c = 0; c < cols; c++) {
                colToStr(c, hold);
                if (w == hold) goto bypass;
            }
        }
        return false;
        bypass:
        continue;
    }
    _solutions.append(_state);
    return _exit_on_first;
}

void Solver::increaseProg(int amount)
{
    int pc = _inv * (_progress += amount); //(100 * (_progress += amount)) / _total;

    if (pc != _percent) {
        _percent = pc;
        emit progressChanged(_percent);
    }
}

void Solver::workAsync(const QStringList &needed)
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
    WordList WL;
    QString x = word.left(1);

    if (_row_words.hasWord(word)) {
        WL.selectStartWith(x, _col_words);
        setTotal( (_state.rows() - 1) * _col_words.length() + WL.length() - _id );

        if (RW_first(0, word, WL)) { completed(); return; }
        for (int r = 1; r < _state.rows(); r++)
            if (RW_first(r, word, _col_words)) { completed(); return; }
    } else {
        WL.selectStartWith(x, _row_words);
        setTotal( (_state.cols() - 1) * _row_words.length() + WL.length() - _id );

        if (CW_first(0, word, WL)) return completed();
        for (int c = 1; c < _state.cols(); c++)
            if (CW_first(c, word, _row_words)) { completed(); return; }
    }
    completed();
}

