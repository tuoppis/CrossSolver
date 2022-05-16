#ifndef ANAGRAMSOLVER_H
#define ANAGRAMSOLVER_H

#include <QObject>
#include "wordlist.h"

class AnagramSolver : public QObject
{
    Q_OBJECT
private:
    WordList _dict;
    WordList _words;

    void partialCycle(QString& str, int pos, int minlength);
    bool fullCycle(QString& str, int pos, int w_end, int w_count, int maxwords);
public:
    explicit AnagramSolver(QObject *parent = nullptr);
    explicit AnagramSolver(const WordList& dict): _dict(dict) {}

    QStringList partialSolve(const QString& str, int minlength = 0);
    QStringList fullSolve(const QString& str, int maxwords = 0);
    QStringList wordSolve(const QString& str) { return fullSolve(str, 1); }

    const WordList& dictionary() const { return _dict; }
signals:

public slots:

};

#endif // ANAGRAMSOLVER_H
