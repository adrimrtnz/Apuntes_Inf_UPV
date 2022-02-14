module com.ipc.calculadora {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.ipc.calculadora to javafx.fxml;
    exports com.ipc.calculadora;
}