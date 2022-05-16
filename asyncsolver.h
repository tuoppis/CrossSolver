#ifndef ASYNCSOLVER_H
#define ASYNCSOLVER_H

#include <QObject>
#include <QThread>
//#include <QUrl>
#include <QElapsedTimer>
#include "exsolver.h"

class AsyncSolver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(int solutions READ solutions NOTIFY solutionsChanged)
    Q_PROPERTY(QString dictionary READ dictionary WRITE setDictionary NOTIFY dictionaryChanged)
    Q_PROPERTY(QString resultsIn READ resultsIn WRITE setResultsIn NOTIFY resultsInChanged)
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(bool extendedInfo READ extendedInfo WRITE setExtendedInfo NOTIFY extendedInfoChanged)
public:
    explicit AsyncSolver(QObject *parent = nullptr);

    void clear();

    int progress() const { return _percent; }
    void setProgress(int prog) {
        prog = qMax(0, qMin(100, prog));
        if (prog != _percent) {
            _percent = prog;
            emit progressChanged(_percent);
        }
    }

    int solutions() const { return _results.count(); }

    QString dictionary() const { return _url; }
    void setDictionary(const QString& location);

    Q_INVOKABLE QString rowsAt(int idx) const {
        return (idx >= 0 && idx < _results.length()) ? _results.at(idx).toString(): "";
    }

    Q_INVOKABLE QString columnsAt(int idx) const {
        return (idx >= 0 && idx < _results.length()) ? _results.at(idx).columnsToString(): "";
    }

    Q_INVOKABLE QString comboAt(int idx) const {
        return (idx >= 0 && idx < _results.length()) ? _results.at(idx).comboString(): "";
    }

    QString resultsIn() const { return _savedLoc; }
    void setResultsIn(const QString& url) {
        if (url == _savedLoc) return;
        _savedLoc = url;
        emit resultsInChanged(_savedLoc);
    }
    bool isWorking() const { return _worksrunning != 0; }

    bool extendedInfo() const { return _ext_info; }
    void setExtendedInfo(bool value);
    Q_INVOKABLE bool saveResultsTo(const QString& url, QString heading = QString()) const;
    Q_INVOKABLE int dictionaryWords() const { return _dictionary.count(); }
    bool saveResultsTo(QTextStream& stream, QString heading = QString()) const;

signals:
    void resultsReady(bool hasSolutions);
    void progressChanged(int percent);
    void solutionsChanged(int sols);
    void beginWork(const QStringList& needed);
    void dictionaryChanged(const QString& url);
    void canceled(bool hasPartialResults);
    void isWorkingChanged(bool val);
    void resultsInChanged(const QString& url);
    void extendedInfoChanged(bool status);

public slots:
    void beginAsync(const exsolver& solver, const QStringList& needed_words);
    void beginAsync(int width, int height, const QString& words);
    void cancelWork();
protected slots:
    void receiveProgess(int id, int percent);
    void receiveCompletion(int id);

private:
    QList<QThread*> _threads;
    QList<exsolver*> _solvers;
    QList<exsolver::State> _results;
    QList<int> _progresses;
    WordList _dictionary;
    QString _url;
    QString _savedLoc;
    QElapsedTimer _timer;



    int _percent;
    int _worksrunning;
    QStringList _needed_words;
    bool _ext_info;

};

#endif // ASYNCSOLVER_H
