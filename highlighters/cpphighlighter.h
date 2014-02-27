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
    QTextCharFormat quoteFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat includeFormat;
    QTextCharFormat chevronFormat;
    QTextCharFormat templateFormat;
    QTextCharFormat multiLineCommentFormat;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

private:
    void AddKeywordsRule();
    void AddFunctionsRule();
    void AddCommentsRule();
    void AddTypesRule();
    void AddQuoteRule();
    void AddNumberRule();
    void AddIncludeRule();
    void AddChevronsRule();
    void AddTemplateRule();

};

#endif // CPPHIGHLIGHER_H
