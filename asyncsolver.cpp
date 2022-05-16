#include "asyncsolver.h"

AsyncSolver::AsyncSolver(QObject *parent) :
    QObject(parent), _worksrunning(0), _ext_info(false)
{
    int num = qMax(1, QThread::idealThreadCount());
    for (int i = 0; i < num; i++) {
        _threads.append(new QThread(this));
    }
}

void AsyncSolver::clear()
{
    for (auto th: _threads) {
        th->quit();
        th->wait();
    }
    _solvers.clear();
    _results.clear();
    _progresses.clear();
    _needed_words.clear();
    _worksrunning = 0;
    setProgress(0);
    emit solutionsChanged(0);
}

void AsyncSolver::setDictionary(const QString &location)
{
    if (location == _url) return;


//    QString fname = location.toLocalFile();

    if (location.endsWith(".z")) _dictionary.loadcomp(location);
    else if (location.endsWith(".dic")) _dictionary.loaddic(location);
    else _dictionary.load(location);
//    _dictionary.savecomp("dictionary.z");
    _url = location;
    emit dictionaryChanged(location);
}

void AsyncSolver::setExtendedInfo(bool value) {
    if (value == _ext_info) return;
    emit extendedInfoChanged(_ext_info = value);
}

void AsyncSolver::beginAsync(int width, int height, const QString &words)
{
    exsolver s(height, width, _dictionary);
    auto list = words.toUpper().split(' ', QString::SkipEmptyParts);
    beginAsync(s, list);
}

void AsyncSolver::beginAsync(const exsolver &solver, const QStringList &needed_words)
{
    clear();

    if (_ext_info) {
        _timer.start();
    }
    _needed_words = needed_words;
    _worksrunning = _threads.count();
    for (int i = 0; i < _worksrunning; i++) {
        exsolver* solv = new exsolver(solver, i, _worksrunning);
        QThread* wt = _threads[i];
        solv->moveToThread(wt);
        connect(wt, &QThread::finished, solv, &QObject::deleteLater);
        connect(this, &AsyncSolver::beginWork, solv, &exsolver::beginWork);
        connect(solv, &exsolver::progressChanged, this, &AsyncSolver::receiveProgess);
        connect(solv, &exsolver::workCompleted, this, &AsyncSolver::receiveCompletion);
        _solvers.append(solv);
        _progresses.append(0);
        wt->start();
    }
    emit beginWork(_needed_words);
    emit isWorkingChanged(true);
}

void AsyncSolver::cancelWork()
{
    if (isWorking()) {
        emit isWorkingChanged(false);
    }
    clear();
    if (_ext_info) {

    }
    emit canceled(false);
}

void AsyncSolver::receiveProgess(int id, int percent)
{
    _progresses[id] = percent;
    if ((percent > _percent) || (_percent >= 100)) {
        int tot = 0;
        for (int i: _progresses) tot += i;
        setProgress(tot / _progresses.count());
    }
}

QString adjtime(qint64 msec)
{
    int t = (msec / 1000);

    QString res = QString("%1.%2s").arg(t % 60, 2).arg(int(msec % 1000), 3, 10, QChar('0'));
    if ((t /= 60) == 0) return res;
    res.prepend(QString("%1m").arg(t % 60, 2));
    if ((t /= 60) == 0) return res;
    res.prepend(QString("%1h").arg(t % 60, 2));
    if ((t /= 24) == 0) return res;
    res.prepend(QString("%1d").arg(t, 2));
    return res;
}

void AsyncSolver::receiveCompletion(int id)
{
    _results.append(_solvers[id]->solutions());
    _threads[id]->quit();
    if (--_worksrunning == 0) {
        qint64 time = _timer.elapsed();
        QString head;
        if (_ext_info) {
            head = tr("number of threads: %1\nrunning time: %2").arg(_threads.count()).arg(adjtime(time));
        }
        emit isWorkingChanged(false);
        emit resultsReady(true);
        if (!_savedLoc.isEmpty()) saveResultsTo(_savedLoc, head);
        setProgress(0);
    }
    emit solutionsChanged( solutions() );
}

bool AsyncSolver::saveResultsTo(const QString &url, QString heading) const
{
    QFile file(url);

    if (file.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        saveResultsTo(stream, heading);
        file.close();
        return true;
    }
    return false;
}

bool AsyncSolver::saveResultsTo(QTextStream &stream, QString heading) const
{
    stream << tr("%1 RESULTS FOR '%2'\n").arg(_results.count()).arg(_needed_words.join(' '));
    stream << heading << '\n';
    for (const exsolver::State &s: _results) {
        stream << s.comboString() << '\n';
    }
    return true;
}
