import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import com.crossword.solver 1.0

GroupBox {
    id: window
    width: 250
    height: 150
    flat: true

    Solver {
        id: solver
        dictionary: ":/files/dictionary.dic"
        resultsIn: "results.txt"

        onResultsReady: {
            start_button.state = "";
            out_txt.state = "RESULTS"
        }
    }

    ColumnLayout {
        anchors.fill: parent
    
        RowLayout {
            Label { text: "Dimensions:" }
            SpinBox {
                id: dimWidth
                maximumValue: 10
                minimumValue: 3
                width: 100
            }
            Label { text: "X" }
            SpinBox {
                id: dimHeight
                maximumValue: 10
                minimumValue: 3
                width: 100
            }
        }

        Label { text: "Contains:" }
        TextField {
            id: mustWords
            Layout.fillWidth: true
            onTextChanged: {
                start_button.enabled =
                        (text.length >= dimHeight.value) && (text.length >= dimWidth.value);
            }
        }


        RowLayout {

            Button {
                id: start_button
                text: "Start"
                onClicked: {
                    state = "WORKING"
                    beginwork();
                }
                states:
                    State {
                        name: "WORKING"
                        PropertyChanges {
                            target: start_button;
                            enabled: false;
                        }
                        PropertyChanges {
                            target: start_button
                            text: "Working"
                        }
                        PropertyChanges {
                            target: stop_button
                            enabled: true
                        }
                        PropertyChanges {
                            target: progress
                            visible: true
                        }
                        PropertyChanges {
                            target: dimHeight
                            enabled: false
                        }
                        PropertyChanges {
                            target: dimWidth
                            enabled: false
                        }
                        PropertyChanges {
                            target: mustWords
                            enabled: false
                        }
                    }
            }

            Button {
                id: stop_button
                text: "Stop"
                enabled: false
                onClicked: {
                    if (solver.isWorking) solver.cancelWork();
                    start_button.state = "";
                }
            }

            Label {
                id: out_txt
                text: "No Results yet"
                states: State {
                    name: "RESULTS"
                    PropertyChanges {
                        target: out_txt
                        text: "Results: " + solver.solutions;
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }

        ProgressBar {
            id: progress
            minimumValue: 0
            maximumValue: 100
            Layout.fillWidth: true

            value: solver.progress
            visible: false
        }

    }

    function beginwork() {
        solver.beginAsync(dimWidth.value, dimHeight.value, mustWords.text);
    }

    Component.onCompleted: start_button.enabled = false
}
