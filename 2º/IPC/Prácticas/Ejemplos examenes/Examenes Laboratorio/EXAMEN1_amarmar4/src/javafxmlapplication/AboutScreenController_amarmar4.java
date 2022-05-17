/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlapplication;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Adrián Martínez
 */
public class AboutScreenController_amarmar4 implements Initializable {

    @FXML
    private Label nameLabel;
    @FXML
    private Label dniLabel;
    @FXML
    private Button acceptBtn;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        acceptBtn.setOnAction(e -> {
            Stage stage = (Stage) acceptBtn.getScene().getWindow();
            stage.close();
            
        });
    }    
    
}
