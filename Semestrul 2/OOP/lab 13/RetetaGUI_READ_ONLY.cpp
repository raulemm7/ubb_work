//
// Created by raulo on 5/30/2024.
//

#include "RetetaGUI_READ_ONLY.h"

void RetetaReadOnlyGUI::paintEvent(QPaintEvent *ev) {
    QPainter element{ this };
    for (int i = 0; i < this->nr_meds; i++) {
        int numarRandom = std::rand() % 5;
        int numarRandomX = std::rand() % (width() - 50);
        int numarRandomY = std::rand() % (height() - 50);
        int elementWidth = std::rand() % 50 + 10;
        int elementHeight = std::rand() % 50 + 10;
        QColor culoare = culoareRandom();
        element.setPen(culoare);
        element.setBrush(culoare);
        switch (numarRandom) {
            case 0:
                element.drawLine(numarRandomX, numarRandomY, elementWidth, elementHeight);
                break;
            case 1:
                element.drawRect(numarRandomX, numarRandomY, elementWidth, elementHeight);
                break;
            case 2:
                element.drawArc(numarRandomX, numarRandomY, elementWidth, elementHeight, 0, 5760);
                break;
            case 3:
                element.drawEllipse(numarRandomX, numarRandomY, elementWidth / 2, elementHeight / 2);
                break;
            case 4:
                element.drawPie(numarRandomX, numarRandomY, elementWidth, elementHeight, 0, 5760);
                break;
            default:
                break;
        }
    }
}

QColor RetetaReadOnlyGUI::culoareRandom() {
    int rosu = std::rand() % 256;
    int verde = std::rand() % 256;
    int albastru = std::rand() % 256;
    return {rosu, verde, albastru};
}
