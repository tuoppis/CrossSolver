#ifndef SOLVER_H
#define SOLVER_H

#include "wordlist.h"
#include <QThread>

class Solver: public QObject
{
    Q_OBJECT

public:
    class State {
    private:
        QChar *_state;
        int _rows;
        int _cols;
    public:
        State(): _state(nullptr), _rows(0), _cols(0) {}
        State(int rows, int cols): _state(new QChar[rows * cols]), _rows(rows), _cols(cols) {}
        State(const State& cpy): _state(new QChar[cpy._rows * cpy._cols]), _rows(cpy._rows), _cols(cpy._cols) {
            for (int i = 0; i < (_rows*_cols); i++) _state[i] = cpy._state[i];
        }
        State(State&& mve): _rows(mve._rows), _cols(mve._cols), _state(mve._state) { mve._state = nullptr; }
        ~State() { delete[] _state; }

        QChar& get(int row, int col) { return _state[row * _cols + col]; }
        const QChar& get(int row, int col) const { return _state[row * _cols + col]; }
        void fillWithRow(int row, QString& val) const {
            val.clear();
            val.append(&get(row, 0), _cols);
        }
        void fillWithCol(int col, QString& val) const {
            val.clear();
            for (int r = 0; r < _rows; r++) val.append( get(r, col) );
        }

        State& operator = (const State& cpy) {
            int sz1 = length();
            int sz2 = cpy.length();
            if (sz1 != sz2) {
                delete [] _state;
                _state = new QChar[sz2];
            }
            _rows = cpy._rows;
            _cols = cpy._cols;
            for (int i = 0; i < sz2; i++) _state[i] = cpy._state[i];
            return *this;
        }

        State& operator = (State&& mve) {
            delete [] _state;
            _rows = mve._rows;
            _cols = mve._cols;
            _state = mve._state;
            mve._state = nullptr;
            return *this;
        }

        int rows() const { return _rows; }
        int cols() const { return _cols; }
        int length() const { return _rows * _cols; }

        QString toString() const {
            QString res(_rows * (_cols + 1), '\0');
            for (int r = 0; r < _rows; r++) {
                res.append(&get(r, 0), _cols);
                res.append('\n');
            }
            return res;
        }

        QString columnsToString() const {
            QString res(_cols * (_rows + 1), '\0');
            QString col(_rows, '\0');
            res.clear();
            for (int c = 0; c < _cols; c++) {
                fillWithCol(c, col);
                res.append(col).append('\n');
            }
            return res;
        }

        QString comboString() const {
            QString col(_rows, '\0');
            QString res(2 * (_cols + 1) * (_rows + 1), '\0');

            res.clear();
            if (_rows >= _cols) {
                for (int i = 0; i < _cols; i++) {
                    fillWithCol(i, col);
                    res.append(&get(i, 0), _cols).append('\t');
                    res.append(col).append('\n');
                }
                for (int r = _cols; r < _rows; r++) {
                    res.append(&get(r, 0), _cols).append('\n');
                }
            } else {
                for (int i = 0; i < _rows; i++) {
                    fillWithCol(i, col);
                    res.append(col).append('\t');
                    res.append(&get(i, 0), _cols).append('\n');
                }
                for (int c = _rows; c < _cols; c++) {
                    fillWithCol(c, col);
                    res.append(col).append('\n');
                }
            }
            return res;
        }
    };

    Solver(int rows, int cols, const WordList& words);
    Solver(const Solver& init, int id = 0, int step = 1);

    QList<State> FindAllWith(QStringList words);

    const State& state() const { return _state; }
    const QList<State>& solutions() const { return _solutions; }
    int percent() const { return _percent; }

    void setId(int id) { _id = id; }
    void setStep(int step) { _step = step; }

//    void FindAllAsync(QStringList needed_words);
signals:
    void progressChanged(int percent);
    void workCompleted(int id);

public slots:
    void workAsync(const QStringList& needed);

protected:
    WordList _col_words;
    WordList _row_words;

    State _state;
    QList<State> _solutions;
    QStringList _needed;

    int _progress;
    int _total;
    int _percent;
    int _id;
    int _step;

    float _inv;

    bool _exit_on_first;

    Solver() {}

    bool RW_first(int row_idx, const QString& row_word, const WordList& COL_WL);
    bool RW_Row(int row, int col, int row_idx, const QString& row_word, const WordList& ROW_WL);
    bool RW_Col(int row, int col, int row_idx, const QString& row_word, const WordList& COL_WL);

    bool CW_first(int col_idx, const QString& col_word, const WordList& ROW_WL);
    bool CW_Row(int row, int col, int col_idx, const QString& col_word, const WordList& ROW_WL);
    bool CW_Col(int row, int col, int col_idx, const QString& col_word, const WordList& COL_WL);

    bool Row(int row, int col, const WordList& ROW_WL);
    bool Col(int row, int col, const WordList& COL_WL);

    bool testSolutionAt(int row, int col);

    void colToStr(int col, QString& str) {
        for (int r = 0; r < str.length(); r++) str[r] = _state.get(r, col);
    }

    void rowToStr(int row, QString& str) {
        for (int c = 0; c < str.length(); c++) str[c] = _state.get(row, c);
    }

    void strToCol(int row, int col, const QString& str) {
        for (int r = row; r < _state.rows(); r++) _state.get(r, col) = str.at(r);
    }

    void strToRow(int row, int col, const QString& str) {
        for (int c = col; c < _state.cols(); c++) _state.get(row, c) = str.at(c);
    }


    bool wordsFromRow(int row, QString& str, WordList& list);
    bool wordsFromCol(int col, QString& str, WordList& list);

    void increaseProg(int amount);

    bool FindAll(int id, int step);

    void setTotal(int val) { _total = qMax(1, val);  _inv = 100.0f / _total; }

    void completed() { emit workCompleted(_id); }
};

#endif // SOLVER_H
