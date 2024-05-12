#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include "Processor.h"

class SimulatorGUI : public QWidget {
public:
    SimulatorGUI() {
        // Layout
        QVBoxLayout* layout = new QVBoxLayout(this);

        // Buttons and input fields
        QPushButton* startButton = new QPushButton("Start Simulation", this);
        layout->addWidget(startButton);
        connect(startButton, SIGNAL(clicked()), this, SLOT(startSimulation()));

        QLabel* dataForwardingLabel = new QLabel("Enable Data Forwarding (1 for Yes, 2 for No):", this);
        layout->addWidget(dataForwardingLabel);
        dataForwardingInput = new QLineEdit(this);
        layout->addWidget(dataForwardingInput);

        QLabel* latencyChangeLabel = new QLabel("Enter Latency Change (1 for Yes, -1 to Stop):", this);
        layout->addWidget(latencyChangeLabel);
        latencyChangeInput = new QLineEdit(this);
        layout->addWidget(latencyChangeInput);

        // Output label
        outputLabel = new QLabel(this);
        layout->addWidget(outputLabel);

        setLayout(layout);
    }

private slots:
    void startSimulation() {
        // Get user inputs
        int enable = dataForwardingInput->text().toInt();
        int latencyChange = latencyChangeInput->text().toInt();

        // Run simulation
        Processor sim;
        // Simulate your processor based on user inputs
        // ...

        // Display register contents after every cycle
        std::string output = "Register Contents After Every Cycle:\n";
        // Fetch register contents from sim and append to output
        // ...

        outputLabel->setText(QString::fromStdString(output));
    }

private:
    QLineEdit* dataForwardingInput;
    QLineEdit* latencyChangeInput;
    QLabel* outputLabel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SimulatorGUI gui;
    gui.setWindowTitle("Simulator GUI");
    gui.show();
    return app.exec();
}

