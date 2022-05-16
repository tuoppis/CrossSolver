#ifndef WORDLIST_H
#define WORDLIST_H

#include <memory>
#include <functional>
#include <QStringList>
#include <QList>
#include <QByteArray>
#include <QUrl>
#include <QtCore>

class WordList;

typedef std::shared_ptr<WordList> WordListPtr;

class WordList : public QStringList
{
//    Q_OBJECT

public:
    class Span {
    public:
        int start;
        int end;
        Span(): start(0), end(0) {}
        Span(int st, int en): start(st), end(en) {}
        Span(const Span& sp): start(sp.start), end(sp.end) {}
        bool isEmpty() const { return end <= start; }
        int length() const { return end - start; }
    };

    WordList(): QStringList() {}
    WordList(const WordList& cpy): QStringList(cpy) {}
    WordList(const QUrl& url): QStringList() { load(url.toLocalFile()); }

    WordList get(std::function<bool (const QString&)> predicate) const;
    WordList getStartWith(QString& str) const;
    int countStartWith(QString& str) const;
    int countStartWith(QString &str, bool& exist) const;
    int FindPosition(const QString& str) const { return sortPos(str); }

    bool hasWord(const QString& word) const { return sortExists(word) >= 0; }
    bool addWord(const QString& word) {
        int pos = sortExists(word);
        if (pos < 0) insert(~pos, word);
        return (pos < 0);
    }


    bool selectByLambda(std::function<bool (const QString&)> predicate, const WordList& from);
    bool selectStartWith(QString& str, const WordList& from);
    const Span spanStartingWith(QString& str) const;
    const Span spanStartingWith(QString &str, const Span& span) const;

    bool load(const QString& filename);
    bool save(const QString& filename) const;

    bool loadcomp(const QString& filename);
    bool savecomp(const QString& filename) const;

    bool loaddic(const QString& filename);
/*    bool load(const QUrl& url) {
        return load(url.toLocalFile());
    }*/
/*
    static WordListPtr create() {
        return std::make_shared<WordList>();
    }
*/
signals:

public slots:

private:
    int sortExists(const QString& str, int startAt = 0) const;
    int sortPos(const QString& str, int startAt = 0) const;
    int sortExists(const QString& str, const Span& span) const;
    int sortPos(const QString& str, const Span& span) const;
};

#endif // WORDLIST_H
