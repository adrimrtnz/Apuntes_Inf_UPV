module com.example.login_form {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.login_form to javafx.fxml;
    exports com.example.login_form;
}