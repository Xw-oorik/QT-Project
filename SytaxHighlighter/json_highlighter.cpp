#include "json_highlighter.h"


JsonHighlighter::JsonHighlighter(QTextDocument *parent):QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // 1. 值-数字
    //    rule.pattern = QRegularExpression("-{0,1}[0-9]{0,}\\.{0,1}[0-9]{0,}");
    rule.pattern = QRegularExpression("-?\\d+\\.?\\d*");  // 上面写法的精简写法
    numberFormat.setForeground(QColor(75, 131, 231));
    numberFormat.setFontFamily("Consolas");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    // 2. 值-字符串
    //    rule.pattern = QRegularExpression("\".*\"");  // 除换行外的任意字符，出现0次或多次。
    rule.pattern = QRegularExpression("\"[^\".]*\"");  // 如果按上边写法:"capital": "hangzhou" 会匹配到一整行，而不是单独的"capital" 和 "hangzhou"
    stringFormat.setForeground(Qt::darkGreen);
    stringFormat.setFontFamily("Consolas");
    rule.format = stringFormat;
    highlightingRules.append(rule);

    // 3. 值-布尔
    rule.pattern = QRegularExpression("true|false");
    boolFormat.setForeground(QColor(242, 129, 142));
    boolFormat.setFontFamily("Consolas");
    rule.format = boolFormat;
    highlightingRules.append(rule);

    // 4. 值-null
    rule.pattern = QRegularExpression("null");
    nullFormat.setForeground(Qt::gray);
    nullFormat.setFontFamily("Consolas");
    rule.format = nullFormat;
    highlightingRules.append(rule);

    // 5. 键
    //    rule.pattern = QRegularExpression("(\"\\w+\")\\s*:\\s*");  // \w: 匹配字母、数字、下划线。等价于[A-Za-z0-9_]
    rule.pattern = QRegularExpression("\"\\w+\"(?=\\s*:)");  // \w: 匹配字母、数字、下划线。等价于[A-Za-z0-9_]
    //    rule.pattern = QRegularExpression(R"(("\w+")\s*:\s*)");  // 用R字符串替换前面一行，更简洁
    keyFormat.setForeground(Qt::darkBlue);
    keyFormat.setFontWeight(QFont::Bold);
    keyFormat.setFontFamily("Consolas");
    rule.format = keyFormat;
    highlightingRules.append(rule);
}

void JsonHighlighter::highlightBlock(const QString &text)
{
    for(const auto& rule:highlightingRules){
        QRegularExpressionMatchIterator matchit = rule.pattern.globalMatch(text);
        while(matchit.hasNext()){
            QRegularExpressionMatch rel = matchit.next();
            setFormat(rel.capturedStart(),rel.capturedLength(),rule.format);
        }
    }
}
