#include <iostream>
#include "anagramsolver.h"

AnagramSolver::AnagramSolver(QObject *parent) :
    QObject(parent)
{
}

void swap(QString& str, int idx1, int idx2)
{
    QChar* ptr = str.data();
    qSwap(ptr[idx1], ptr[idx2]);
}


QStringList AnagramSolver::partialSolve(const QString &str, int minlength)
{
    QStringList res;
    QString pool = str;

    _words.clear();
    for (int i = 0; i < str.length(); i++) {
        swap(pool, 0, i);
        partialCycle(pool, 1, minlength);
        swap(pool, 0, i);
    }
    res = _words;
    return res;
}

void AnagramSolver::partialCycle(QString &str, int pos, int minlength)
{
    auto part = str.left(pos);
    bool exists;
    if (_dict.countStartWith(part, exists) <= 0) return;
    if ((pos >= minlength) && exists) _words.addWord(part);

    for (int i = pos; i < str.length(); i++) {
        swap(str, pos, i);
        partialCycle(str, pos + 1, minlength);
        swap(str, pos, i);
    }
}

QStringList AnagramSolver::fullSolve(const QString &str, int maxwords)
{
    QStringList res;
    QString pool = str;
//    QTextStream stream(stdout);

    if (maxwords <= 0) maxwords = 1 + str.length() / 3;
    _words.clear();
    float f = 100.0f/str.length();
    for (int i = 0; i < str.length(); i++) {
        swap(pool, 0, i);
        fullCycle(pool, 1, 0, 0, maxwords);
        std::cerr << int((i + 1)*f) <<"%\r";

        swap(pool, 0, i);
    }
    res = _words;
    return res;
}

QString processString(const QString& str)
{
    QStringList tmp;
    int pos = 0;
    for (int i = 0; i < str.length(); i++)
    {
        QChar t = str[i];
        if (t.isLower()) {
            QString x = str.mid(pos, i + 1 - pos);
            x[i - pos] = t.toUpper();
            tmp << x;
            pos = i + 1;
        }
    }
    if (pos < str.length()) tmp << str.mid(pos);
    tmp.sort();
    return tmp.join(QChar(' '));
//    return str;
}

bool AnagramSolver::fullCycle(QString &str, int pos, int w_end, int w_count, int maxwords)
{
    auto part = str.mid(w_end, pos - w_end);
    bool exists;
    if (_dict.countStartWith(part, exists) <= 0) return false;
    if (pos == str.length()) {
        if (exists && (part.length() > 1)) {
            _words.addWord(processString(str));
        }
        return exists;
    }
    if ((w_count < maxwords) && exists && (part.length() > 1)) { // start new word
        str[pos - 1] = str[pos - 1].toLower();
        for (int i = pos; i < str.length(); i++) {
            swap(str, pos, i);
            fullCycle(str, pos + 1, pos, w_count + 1, maxwords);
            swap(str, pos, i);
        }
        str[pos - 1] = str[pos - 1].toUpper();
    }
    for (int i = pos; i < str.length(); i++) { // continue extending old one
        swap(str, pos, i);
        fullCycle(str, pos + 1, w_end, w_count, maxwords);
        swap(str, pos, i);
    }
    return false;
}

