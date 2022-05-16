#include <QtGui/QGuiApplication>
#include <QtQml>
#include <QRegExp>
#include <iostream>
#include "qtquick2applicationviewer.h"
#include "asyncsolver.h"
#include "anagramsolver.h"

static QString ver_info =
        "Simplistic crossword solver v. 0.1.\n"
        "LICENCE: GNU GPLv3\n"
        ""
        "";
static QString help_str =
        "HELP\n"
        ""
        "";
static QTextStream ConOut(stdout);
bool processArgs(const QStringList& args);
void doAnagram(AnagramSolver& solv, const QString& str, bool full);

int main(int argc, char *argv[])
{
//    std::cout << "Is this showing?"<<std::endl;
    QGuiApplication app(argc, argv);
    if ( processArgs(app.arguments()) ) return 0;
    QtQuick2ApplicationViewer viewer;


    ConOut.flush();

    qmlRegisterType<AsyncSolver>("com.crossword.solver", 1, 0, "Solver");
    viewer.setMainQmlFile(QStringLiteral("qml/CrossSolver/main.qml"));
//    viewer.setMainQmlFile(QStringLiteral("qrc:/files/main.qml"));



    viewer.showExpanded();

    return app.exec();
}
[[noreturn]]
void error(QString msg)
{
    ConOut << msg << "\n";
    exit(0);
}

typedef std::function<bool (const QString&)> StringPredicate;

class param {
private:
    int _id;
    int _count;
    QRegExp _regexp;
    QString _desc;
    QString _usage;
    QString _error;
    bool _only;
    bool _captures;
    StringPredicate _action;
public:
    enum RESULT { UNMATCHED = -1, SUCCESS = 0, FAILURE = 1, OVERUSE = 2 };
/*    param(int id, const QString& regexp): param(id, regexp, QString(), QString(), false) {}
    param(int id, const QString& regexp, const QString& desc, const QString& usage, bool isOnly = false):
        _id(id), _regexp(regexp), _desc(desc), _usage(usage), _only(isOnly)
    {
        _captures = !_only && regexp.contains(QChar('='));
    }*/
    param(int id, const QString& re, const QString& de, const QString& us, const QString& er, StringPredicate action, bool only = false):
        _id(id), _regexp(re), _desc(de), _usage(us), _error(er), _action(action), _only(only)
    {
        _count = 0;
        _captures = re.contains(QChar('='));
    }

    bool matches(const QString& test) const { return _regexp.exactMatch(test); }
//    QRegExp& reg() { return _regexp; }
    const QRegExp& reg() const { return _regexp; }
//    QString& desc() { return _desc; }
    const QString& desc() const { return _desc; }
//    QString& usage() { return _usage; }
    const QString& usage() const { return _usage; }
    bool onlyAllowed() const { return _only; }
    int id() const { return _id; }
    QString error() const { return (_count > 1) ? QString("too many uses"): _error; }
/*
    QString argument(const QString& test) const {
         return (_captures && matches(test))? test.mid(test.indexOf(QChar('=')) + 1): QString();
    }*/

    RESULT action(const QString& arg) {
        if (_regexp.indexIn(arg, 0) != 0) return UNMATCHED;
        if (_count++) return OVERUSE; //::error(QString("Parameter '%1' used too many times.").arg(arg));
        return _action(_regexp.cap(_captures)) ? SUCCESS: FAILURE;
    }

    operator QString() const {
        return QString(4, ' ') + _usage.leftJustified(26) + _desc + "\n";
    }
};

bool processArgs(const QStringList &args)
{
    if (args.length() < 2) return false; // no arguments
    QStringList arglist = args;

/*    for (const QString& s: args) {
        if (s[0].isLetterOrNumber()) continue;
        arglist << s;
    }*/
    arglist.removeFirst();

    enum ptype {GRID = 1, WORDS = 2, OUTF = 4, DICT = 8, TEST = 16, HELP = 32, VER = 64};

    int r = 0, c = 0;
    QStringList words;
    QString outfile, dictfile, anag;
    bool istest = false;
    bool ishelp = false;

    QList<param> plist;
    plist << param(GRID,
                   "^(?:--grid|/g)=(\\d+x\\d+)$",
                   "Sets the grid with width <W> and height <H>.",
                   "--grid=<W>x<H>, /g=<...>",
                   "parameters not > 0.",
                   [&] (const QString& var) {
                        int p = var.indexOf('x');
                        c = var.left(p).toInt();
                        r = var.mid(p + 1).toInt();
                        return (c * r) > 0;
                   }
                   )
          << param(WORDS,
                   "^(?:--words|/w)=(\\w+(?:\\s*[,;/+]*\\s*\\b\\w+)*)$",
                   "The words that need to be in the grid.",
                   "--words=\"w1 w2\", /w=<...>",
                   "no words defined.",
                   [&] (const QString& var) {
                        auto tmp = var.split(QRegExp("\\b\\s*[,;/+]?\\s*\\b"), QString::SkipEmptyParts);
                        for (auto s: tmp) {
                            words << s.toUpper();
                        }
                        return !words.isEmpty();
                   }
                   )
          << param(OUTF,
                   "^(?:--out|/o)=(.*)",
                   "The filename to save the results to. If none is set, displays results on the terminal.",
                   "--out=\"fname\", /o=<...>",
                   "file could not be opened.",
                   [&] (const QString& var) {
                        outfile = var;
                        QFile file(outfile);
                        bool isopenable = file.open(QFile::WriteOnly | QFile::Append);
                        file.close();
                        return isopenable;
                   }
                   )
          << param(DICT,
                   "^(?:--dict|/d)=(.*)",
                   "The dictionary to be used.",
                   "--dict=\"fname\", /d=<...>",
                   "could not access the dictionary.",
                   [&] (const QString& var) {
                        dictfile = var;
                        QFile file(dictfile);
                        bool isopenable = file.open(QFile::ReadOnly);
                        file.close();
                        return isopenable;
                   }
                   )
          << param(TEST,
                   "^(?:--test|/t)$",
                   "Makes a test run with fixed parameters.",
                   "--test, /t",
                   "",
                   [&] (const QString& var) {
                        istest = true;
                        //if (args.length() > 3) return false;
                        c = 5;
                        r = 4;
                        return true;
                   }
                   )
          << param(HELP,
                   "^(?:--help|/h)$",
                   "Displays help.",
                   "--help, /h",
                   "no other arguments allowed.",
                   [&] (const QString& var) {
                        if (arglist.count() > 1) return false;
                        ishelp = true;
//                        error(help_str);
                        return true;
                   },
                   true)
          << param(VER,
                   "^(?:--version|/v)$",
                   "Displays version info",
                   "--version, /v",
                   "no other arguments allowed.",
                   [&] (const QString& var) {
                        if (arglist.count() > 1) return false;
                        error(ver_info);
                        return true;
                   },
                   true)
           << param(VER,
                    "^(?:--anag|/a)=(.*)$",
                    "Searches anagrams for given word.",
                    "--anag=<word>, /a=<...>",
                    "illegal parameter.",
                    [&] (const QString& var) {
                        anag = var.toUpper();
                        //anag.remove(QRegExp("\\W+"));
                        return !anag.isEmpty();
                    }
                    );
    auto iterlist = plist;

    for (const QString& arg: arglist) {
        int pos = 0;
        for (; pos < iterlist.length(); pos++) {
            switch (iterlist[pos].action(arg)) {
            case param::UNMATCHED:
                continue;
            case param::SUCCESS:
                goto loop_end;
            case param::FAILURE:
            default:
                error("Argument '" + arg + "' failed action: " + iterlist[pos].error());
            }
            break;
        }
        error("Argument '" + arg + "' not recognized!");
        loop_end:
        continue;//iterlist.removeAt(pos);
    }

    if (ishelp) {
        ConOut << help_str;
        for (auto p: plist) {
            ConOut << p;
        }
        error("");
    }

    if (istest) {
        if ((c != 5) || (r != 4)) error("Invalid grid size for --test!");
        if (!dictfile.isEmpty()) error("Only default dictionary allowed for --test!");
        QStringList tmplist;
        tmplist << "ELITE" << "SPEED" << "TEST";
        if (!words.isEmpty() && (words != tmplist)) error("Only words '" + tmplist.join("', '") + "' allowed for --test!");
        words = tmplist;
        ConOut << "\nStarting test:";
    }

    if (dictfile.isEmpty()) dictfile = ":/files/english.dic";
    if (outfile.isEmpty()) outfile = "results.txt";

    if (!anag.isEmpty()) {
        WordList dict;
        dict.load(dictfile);
        AnagramSolver asolv(dict);
        doAnagram(asolv, anag, false);
    }


    if ((r * c) == 0) error("Grid dimension were not set.");
    for (auto s: words) {
        int l = s.length();
        if ((r != l) && (c != l)) error("Word '" + s + "' do not match the grid.");
    }


    ConOut << "\nRows: " << r;
    ConOut << "\nColumns: " << c;
    ConOut << "\nWords: " << words.join(", ");
    ConOut << "\nOut: " << outfile;
    ConOut << "\nDictionary: " << dictfile;
    ConOut << "\n";

    return true;
}

void doAnagram(AnagramSolver& solv, const QString &str, bool full)
{
//    auto res = solv.partialSolve(str, 3);
    QStringList res;
    if (str.startsWith(".")) {
        res = solv.partialSolve(str.mid(1), 3);
        ConOut << "Partial words for '" << str <<"':\n";
    }
    else {
        res = solv.fullSolve(str, 2);
        ConOut << "Anagrams for '" << str <<"':\n";
    }
    ConOut << solv.dictionary().length() << " words in the dictionary\n";
    QMultiMap<int, QString> map;
//    QRegExp rep("([a-z])");

    for (auto s: res) {
//        map.insert(s.length(), (s.replace(rep, "\\1 ")).toUpper());
        map.insert(s.length(), s);
//        ConOut << s << '\n';
    }
    for (auto s: map) {
        ConOut << s << '\n';
    }
    ConOut << res.length() << " solutions found.\n";
}
