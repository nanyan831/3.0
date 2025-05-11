// snakegame.cpp
#include "snakegame.h"
#include <QMessageBox>

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800, 600);
    setStyleSheet("background-color: #2c3e50;");
    setFocusPolicy(Qt::StrongFocus);
    initGame();
}

void SnakeGame::initGame()
{
    m_body.clear();
    m_colors.clear();

    // 修正初始化位置为窗口中心
    int startX = width()/2 - DOT_SIZE;
    int startY = height()/2;

    for(int i=0; i<3; ++i){
        m_body.prepend(QPoint(startX + i*DOT_SIZE, startY));
        m_colors.prepend(randomColor());
    }

    spawnFood();
    m_timerId = startTimer(DELAY);
}

QColor SnakeGame::randomColor() const
{
    return QColor::fromHsv(QRandomGenerator::global()->bounded(360),
                           150 + QRandomGenerator::global()->bounded(100),
                           150 + QRandomGenerator::global()->bounded(100));
}

void SnakeGame::spawnFood()
{
    QRandomGenerator *gen = QRandomGenerator::global();

    do {
        m_food.rx() = gen->bounded((width()-DOT_SIZE)/DOT_SIZE) * DOT_SIZE;
        m_food.ry() = gen->bounded((height()-DOT_SIZE)/DOT_SIZE) * DOT_SIZE;
        m_foodColor = randomColor();
    } while(m_body.contains(m_food));
}

void SnakeGame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制食物
    painter.setBrush(m_foodColor);
    painter.drawEllipse(m_food, DOT_SIZE/2, DOT_SIZE/2);

    // 绘制蛇身
    for(int i=0; i<m_body.size(); ++i){
        QColor color = m_colors[i];
        if(i == 0) color = color.darker(150);
        painter.setBrush(color);
        painter.drawEllipse(m_body[i], DOT_SIZE/2, DOT_SIZE/2);
    }

    if(!m_inGame){
        QFont font("Arial", 24, QFont::Bold);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "Game Over\nPress SPACE to restart");
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
