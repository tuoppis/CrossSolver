#include "wordlist.h"
#include <QTextStream>

int WordList::sortExists(const QString& str, int startAt) const
{
    int min = startAt;
    int max = length() - 1;

    while (max >= min) {
        int pos = (min + max) / 2;
        int cmp = str.compare(at(pos));
        if (cmp == 0) return pos;
        (cmp < 0) ? max = pos - 1: min = pos + 1;
    }
    return ~min;
}

int WordList::sortExists(const QString &str, const Span &span) const
{
    int min = span.start;
    int max = span.end - 1;

    while (max >= min) {
        int pos = (min + max) / 2;
        int cmp = str.compare(at(pos));
        if (cmp == 0) return pos;
        (cmp < 0) ? max = pos - 1: min = pos + 1;
    }
    return ~min;
}

int WordList::sortPos(const QString& str, int startAt) const
{
    int min = startAt;
    int max = length() - 1;

    while (max >= min) {
        int pos = (min + max) / 2;
        int cmp = str.compare(at(pos));
        if (cmp == 0) return pos;
        (cmp < 0) ? max = pos - 1: min = pos + 1;
    }
    return min;
}

int WordList::sortPos(const QString &str, const Span &span) const
{
    int min = span.start;
    int max = span.end - 1;

    while (max >= min) {
        int pos = (min + max) / 2;
        int cmp = str.compare(at(pos));
        if (cmp == 0) return pos;
        (cmp < 0) ? max = pos - 1: min = pos + 1;
    }
    return min;
}

WordList WordList::get(std::function<bool (const QString &)> predicate) const
{
    WordList ret;
    ret.selectByLambda(predicate, *this);
    return ret;
}

int WordList::countStartWith(QString& str) const
{
    int pi = sortPos(str, 0);

//    if (pi < 0) pi = ~pi;

    int last = str.length() - 1;
    ushort uc = str[last].unicode();
    str[last] = QChar(uc + 1);

    int pf = sortPos(str, pi);
    str[last] = QChar(uc);

    return pf - pi;
}

int WordList::countStartWith(QString &str, bool &exist) const
{
    int pi = sortExists(str, 0);

    if (pi >= 0) exist = true;
    else { pi = ~pi; exist = false; }

    int last = str.length() - 1;
    ushort uc = str[last].unicode();
    str[last] = QChar(uc + 1);

    int pf = sortPos(str, pi);
    str[last] = QChar(uc);

    return pf - pi;
}

WordList WordList::getStartWith(QString& str) const
{
    int pi = FindPosition(str);
    int last = str.length() - 1;
    ushort uc = str[last].unicode();
    str[last] = QChar(uc + 1);
    int pf = sortPos(str, pi);
    str[last] = QChar(uc);

    WordList ret;
    ret.reserve(pf - pi);
    for (int i = pi; i < pf; i++) ret.append(at(i));
    return ret;
}

bool WordList::selectStartWith(QString &str, const WordList &from)
{
    int pi = from.FindPosition(str);
    int last = str.length() - 1;
    ushort uc = str[last].unicode();
    str[last] = QChar(uc + 1);
    int pf = from.sortPos(str, pi);
    str[last] = QChar(uc);

    clear();
    for (int i = pi; i < pf; i++) append(from[i]);
    return !isEmpty();
}

const WordList::Span WordList::spanStartingWith(QString &str) const
{
    if (str.isEmpty()) return Span(0, length());
    int pi = FindPosition(str);
    int last = str.length() - 1;
    ushort uc = str[last].unicode();
    str[last] = QChar(uc + 1);
    int pf = sortPos(str, pi);
    str[last] = QChar(uc);

    return Span(pi, pf);
}

const WordList::Span WordList::spanStartingWith(QString & str, const WordList::Span& span) const
{
    if (str.isEmpty()) return span;
    int pi = sortPos(str, span);
    int last = str.length() - 1;
    ushort uc = str[last].unicode();
    str[last] = QChar(uc + 1);
    int pf = sortPos(str, Span(pi, span.end));
    str[last] = QChar(uc);

    return Span(pi, pf);
}

bool WordList::selectByLambda(std::function<bool (const QString &)> predicate, const WordList &from)
{
    clear();
    for (auto w: from) if (predicate(w)) append(w);
    return !isEmpty();
}

bool WordList::load(const QString &filename)
{
    QFile file(filename);
    QString line;
//    int len = length();
    clear();

    if (file.open((QFile::ReadOnly))) {
        QTextStream txtStr(&file);
        txtStr.setCodec("UTF-8");
        while (!txtStr.atEnd()) {
            line = txtStr.readLine().toUpper().trimmed();
            if (line.isEmpty()) continue;
/*            int pos = sortExists(line);
            if (pos >= 0) continue;
            insert(~pos, line);*/
            addWord(line);
        }
        file.close();
        return length() > 0;
    } else
        return false;
}

bool WordList::save(const QString &filename) const
{
    QFile file(filename);

    if (file.open(QFile::WriteOnly)) {
        QTextStream textStr(&file);
        textStr.setCodec("UTF-8");
        for (auto w: *this) {
            textStr << w << '\n';
        }
        file.close();
        return true;
    }
    return false;
}

bool WordList::loaddic(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) return false;

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    while (!stream.atEnd()) append(stream.readLine());
    file.close();
    return !isEmpty();
}

bool WordList::loadcomp(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) return false;

    auto data = file.readAll();

    data = qUncompress(data);
    QTextStream stream(&data);
    stream.setCodec("UTF-8");

    while (!stream.atEnd()) {
        append(stream.readLine());
    }
    file.close();
    return !isEmpty();
}

bool WordList::savecomp(const QString &filename) const
{
    QByteArray data;
    QTextStream stream(&data);
    stream.setCodec("UTF-8");
    for (auto w: *this) stream << w << '\n';
    stream.flush();
    data = qCompress(data);

    QFile file(filename);
    if (!file.open(QFile::WriteOnly)) return false;

    file.write(data);
    file.close();
    return true;
}
