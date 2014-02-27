#include "cpphighlighter.h"

CppHighlighter::CppHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent), commentStartExpression("/\\*"),
                                                       commentEndExpression("\\*/")
{
    // The order is important, it determines the union between rules
    AddFunctionsRule();
    AddTypesRule();
    AddNumberRule();
    AddQuoteRule();
    AddIncludeRule();
    AddChevronsRule();
    AddTemplateRule();
    AddKeywordsRule();
    AddCommentsRule();

    multiLineCommentFormat.setForeground(QColor(117,113,94));
}

void CppHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, Rules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }

    setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
}


void CppHighlighter::AddCommentsRule()
{
    HighlightingRule bufferRule;
    singleLineCommentFormat.setForeground(QColor(117,113,94));
    bufferRule.pattern = QRegExp("//[^\n]*");
    bufferRule.format = singleLineCommentFormat;
    Rules.append(bufferRule);
}

void CppHighlighter::AddFunctionsRule()
{
    HighlightingRule bufferRule;
    functionsFormat.setForeground(QColor(145,225,42));
    bufferRule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    bufferRule.format = functionsFormat;
    Rules.append(bufferRule);
}

void CppHighlighter::AddQuoteRule()
{
     HighlightingRule bufferRule;
     quoteFormat.setForeground(QColor(230,219,116));
     bufferRule.pattern = QRegExp("\"([^\"']*)\"");
     bufferRule.format = quoteFormat;
     Rules.append(bufferRule);
}

void CppHighlighter::AddChevronsRule()
{
     HighlightingRule bufferRule;
     chevronFormat.setForeground(QColor(230,219,116));
     bufferRule.pattern = QRegExp("\\s<([^<']*)>");
     bufferRule.format = chevronFormat;
     Rules.append(bufferRule);
}

void CppHighlighter::AddTemplateRule()
{
     HighlightingRule bufferRule;
     templateFormat.setForeground(QColor(102,217,239));
     bufferRule.pattern = QRegExp("[A-Za-z]+<.*>");
     bufferRule.format = templateFormat;
     Rules.append(bufferRule);
}

void CppHighlighter::AddNumberRule()
{
     HighlightingRule bufferRule;
     numberFormat.setForeground(QColor(174,129,255));
     bufferRule.pattern = QRegExp("\\b[0-9]+");
     bufferRule.format = numberFormat;
     Rules.append(bufferRule);
}

void CppHighlighter::AddIncludeRule()
{
     HighlightingRule bufferRule;
     includeFormat.setForeground(QColor(249,38,114));
     bufferRule.pattern = QRegExp("\\#[A-Za-z]+\\b");
     bufferRule.format = includeFormat;
     Rules.append(bufferRule);
}

void CppHighlighter::AddKeywordsRule()
{
    HighlightingRule bufferRule;

    keywordFormat.setForeground(QColor(249,38,114));

    QStringList bufferKeywords;

    bufferKeywords   << "\\bconst\\b"
                     << "\\benum\\b" << "\\bexplicit\\b"
                     << "\\bfriend\\b" << "\\binline\\b"
                     << "\\bnamespace\\b" << "\\boperator\\b"
                     << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                     << "\\bsignals\\b" << "\\bcase\\b" << "\\bswitch\\b"
                     << "\\bslots\\b" << "\\bstatic\\b"
                     << "\\bvirtual\\b" << "\\bif\\b" << "\\belse\\b"
                     << "\\bvolatile\\b" << "\\bnew\\b" << "\\bdelete\\b"
                     << "\\bdelete[]\\b";

    foreach(const QString &pattern, bufferKeywords){
        bufferRule.pattern = QRegExp(pattern);
        bufferRule.format = keywordFormat;
        Rules.append(bufferRule);
    }
}

void CppHighlighter::AddTypesRule()
{
    HighlightingRule bufferRule;

    typesFormat.setForeground(QColor(102,217,239));

    QStringList bufferKeywords;

    bufferKeywords   << "\\bchar\\b" << "\\bclass\\b" << "\\bdouble\\b"
                     << "\\benum\\b" << "\\bint\\b" << "\\blong\\b" << "\\bbool\\b"
                     << "\\bshort\\b" << "\\bsigned\\b" << "\\btypedef\\b"
                     << "\\bstruct\\b" << "\\btemplate\\b" << "\\btypename\\b"
                     << "\\bunsigned\\b" << "\\bunion\\b" << "\\bvoid\\b";

    foreach(const QString &pattern, bufferKeywords){
        bufferRule.pattern = QRegExp(pattern);
        bufferRule.format = typesFormat;
        Rules.append(bufferRule);
    }
}
