#ifndef CPPHIGHLIGHER_H
#define CPPHIGHLIGHER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegExp>
#include <QVector>

class CppHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    CppHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:

    struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };

    QVector<HighlightingRule> Rules;

    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat functionsFormat;
    QTextCharFormat typesFormat;

private:
    void AddKeywordsRule();
    void AddFunctionsRule();
    void AddCommentsRule();
    void AddTypesRule();
};

#endif // CPPHIGHLIGHER_H
