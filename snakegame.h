// snakegame.h
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QRandomGenerator>

class SnakeGame : public QWidget {
    Q_OBJECT

public:
    explicit SnakeGame(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    static constexpr int DOT_SIZE = 20;
    static constexpr int DELAY = 150;

    QVector<QPoint> m_body;
    QVector<QColor> m_colors;
    QPoint m_food;
    QColor m_foodColor;

    bool m_left = false;
    bool m_right = true;
    bool m_up = false;
    bool m_down = false;
    bool m_inGame = true;

    int m_timerId;

    void initGame();
    void spawnFood();
    void checkCollision();
    void move();
    QColor randomColor() const;
};

#endif // SNAKEGAME_H
