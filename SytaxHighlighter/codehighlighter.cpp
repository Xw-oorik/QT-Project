#include "codehighlighter.h"



CodeHighlighter::CodeHighlighter(QTextDocument *parent):QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    keywordFormat.setFontFamily("Consolas");

    //关键字
    QStringList keywordPatterns = {
        "\\bchar\\b", "\\bclass\\b", "\\bconst\\b", "\\bdouble\\b", "\\benum\\b",
        "\\bexplicit\\b", "\\bfriend\\b", "\\binline\\b", "\\bint\\b", "\\blong\\b",
        "\\bnamespace\\b", "\\boperator\\b", "\\bprivate\\b", "\\bprotected\\b", "\\bpublic\\b",
        "\\bshort\\b", "\\bsignals\\b", "\\bsigned\\b", "\\bslots\\b", "\\bstatic\\b",
        "\\bstruct\\b", "\\btemplate\\b", "\\btypedef\\b", "\\btypename\\b", "\\bunion\\b",
        "\\bunsigned\\b", "\\bvirtual\\b", "\\bvoid\\b", "\\bvolatile\\b", "\\bbool\\b",
        "\\bfor\\b", "\\bwhile\\b", "\\bif\\b", "\\belse\\b", "\\bswitch\\b",
        "\\bcase\\b", "\\bbreak\\b", "\\bcontinue\\b", "\\breturn\\b", "\\btry\\b",
        "\\bcatch\\b", "\\bthrow\\b", "\\bnew\\b", "\\bdelete\\b"
    };
    for(const auto &pattern : keywordPatterns){
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //类
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    classFormat.setFontFamily("Consolas");
    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    //数字
    numberFormat.setForeground(QColor(255, 147, 13));
    numberFormat.setFontFamily("Consolas");
    rule.pattern = QRegularExpression("[-+]?\\b[0-9]+(\\.[0-9]*)?\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    // 函数
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");  // 正向预查。只要后边有(，则前面的函数名匹配成功
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    functionFormat.setFontFamily("Consolas");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // 字符串
    // 就是双引号括起来的内容
    rule.pattern = QRegularExpression("\".*\"");  // 除换行外的任意字符，出现0次或多次。
    quotationFormat.setForeground(Qt::darkYellow);
    quotationFormat.setFontFamily("Consolas");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //单行注释
    // 以两个斜杠开始的单行
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    singleLineCommentFormat.setFontFamily("Consolas");
    rule.pattern = QRegularExpression("//[^\n]*");  // 除换行外的任意字符，出现0次或多次。这里也可以写做 "//[.]*"
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);


    //多行注释
    // 也就是被 /* 和 */ 包裹的内容
    multiLineCommentFormat.setForeground(QColor(36, 128, 0));
    multiLineCommentFormat.setFontFamily("Consolas");
    commentStartExpression = QRegularExpression("/\\*");  // 要表示*需要使用两个反斜杠
    commentEndExpression = QRegularExpression("\\*/");
}

void CodeHighlighter::highlightBlock(const QString &text)
{
    //依次匹配
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
    int startIndex;
    if ( previousBlockState() == 1 ) {
        // 如果当前行已经在注释中，也就是之前的行已经找到了开始标识/*, 则从本行从头开始查找结束标识
        startIndex = 0;
    } else {
        // 如果当前行不在注释中, 则从本行查找开始标识
        startIndex = text.indexOf(commentStartExpression);  // 未找到开始标识，则返回-1
    }

    while ( startIndex >= 0 ) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if ( endIndex == -1 ) {
            // 本行未找到结束标识符
            // 说明多行注释未完，设置状态，在下一行接着找结束标识符*/
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            // 本行找到结束标识符
            // 说明多行注释未完，设置状态，在下一行接着找结束标识符*/
            // commentLength = endIndex - startIndex + 2;  // 2 代表字符串 "*/" 的长度
            commentLength = endIndex - startIndex + match.capturedLength();
        }

        //        qDebug() << "startIndex:" << startIndex << ", endIndex:" << endIndex << "commentLength:" << commentLength;
        setFormat(startIndex, commentLength, multiLineCommentFormat);

        // 接着在本行找起始标识符
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
