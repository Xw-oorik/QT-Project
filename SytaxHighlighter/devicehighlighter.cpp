#include "devicehighlighter.h"



DeviceHighlighter::DeviceHighlighter(QTextDocument *parent):QSyntaxHighlighter(parent)
{
    QFont font("Courier", 12);
    HighlightingRule rule;
    // 时间
    rule.pattern = QRegularExpression(R"(\[.*\])");
    timeFormat.setForeground(QColor(85, 85, 85));
    timeFormat.setBackground(QColor(240, 240, 240));
    timeFormat.setFontWeight(QFont::Bold);
    timeFormat.setFont(font);
    rule.format = timeFormat;
    highlightingRules.append(rule);

    // 温度key
    rule.pattern = QRegularExpression("Temperature");
    tempKeyFormat.setForeground(QColor(180, 30, 110));
    tempKeyFormat.setFont(font);
    rule.format = tempKeyFormat;
    highlightingRules.append(rule);

    // 温度value
    rule.pattern = QRegularExpression(R"((?<=Temperature:)\s*-*\d+°C)");
    tempValueFormat.setForeground(QColor(180, 30, 110));
    tempValueFormat.setFontWeight(QFont::Bold);
    tempValueFormat.setFont(font);
    rule.format = tempValueFormat;
    highlightingRules.append(rule);

    // 湿度key
    rule.pattern = QRegularExpression("Humidity");  // +Upper前边的+要转义);
    humiKeyFormat.setForeground(QColor(97, 54, 134));
    //    humiKeyFormat.setForeground(Qt::darkBlue);
    humiKeyFormat.setFont(font);
    rule.format = humiKeyFormat;
    highlightingRules.append(rule);

    // 湿度value
    rule.pattern = QRegularExpression(R"((?<=Humidity:)\s*\d+%)");
    humiValueFormat.setForeground(QColor(97, 54, 134));
    //    humiValueFormat.setForeground(Qt::darkBlue);
    humiValueFormat.setFontWeight(QFont::Bold);
    humiValueFormat.setFont(font);
    rule.format = humiValueFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegularExpression("\(-Normal\)");
    //normalFormat.setForeground(Qt::darkGreen);
    normalFormat.setForeground(Qt::white);
    normalFormat.setBackground(Qt::darkGreen);
    normalFormat.setFont(font);
    rule.format = normalFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegularExpression("\(↓Lower\)");
    lowerFormat.setForeground(Qt::white);
    lowerFormat.setBackground(Qt::darkBlue);
    lowerFormat.setFontWeight(QFont::Bold);
    lowerFormat.setFont(font);
    rule.format = lowerFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegularExpression("\(\↑Upper\)");
    upperFormat.setForeground(Qt::white);
    upperFormat.setBackground(QColor(220, 50, 50));
    upperFormat.setFontWeight(QFont::Bold);
    upperFormat.setFont(font);
    rule.format = upperFormat;
    highlightingRules.append(rule);
}

void DeviceHighlighter::highlightBlock(const QString &text)
{
    for ( const auto& rule : highlightingRules ) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while ( matchIterator.hasNext() ) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
