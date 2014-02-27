#include "cpphighlighter.h"

CppHighlighter::CppHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{
    AddKeywordsRule();
    AddFunctionsRule();
    AddCommentsRule();
    AddTypesRule();
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

void CppHighlighter::AddKeywordsRule()
{
    HighlightingRule bufferRule;

    keywordFormat.setForeground(Qt::darkYellow);

    QStringList bufferKeywords;

    bufferKeywords   << "\\bconst\\b"
                     << "\\benum\\b" << "\\bexplicit\\b"
                     << "\\bfriend\\b" << "\\binline\\b"
                     << "\\bnamespace\\b" << "\\boperator\\b"
                     << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                     << "\\bsignals\\b"
                     << "\\bslots\\b" << "\\bstatic\\b"
                     << "\\bvirtual\\b"
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
                     << "\\benum\\b" << "\\bint\\b" << "\\blong\\b"
                     << "\\bshort\\b" << "\\bsigned\\b" << "\\btypedef\\b"
                     << "\\bstruct\\b" << "\\btemplate\\b" << "\\btypename\\b"
                     << "\\bunsigned\\b" << "\\bunion\\b" << "\\bvoid\\b";

    foreach(const QString &pattern, bufferKeywords){
        bufferRule.pattern = QRegExp(pattern);
        bufferRule.format = typesFormat;
        Rules.append(bufferRule);
    }
}
