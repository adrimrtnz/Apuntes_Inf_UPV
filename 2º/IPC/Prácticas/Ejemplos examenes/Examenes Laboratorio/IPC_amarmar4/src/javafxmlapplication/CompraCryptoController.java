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
import javafx.scene.control.TextField;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Adrián Martínez
 */
public class CompraCryptoController implements Initializable {

    /**
     * Initializes the controller class.
     */
    
    
    @FXML
    private Label actionLabel;
    @FXML
    private TextField amountTextField;
    @FXML
    private Button acceptBtn;
    @FXML
    private Button cancelBtn;
    
    private String accion;
    private String currency;
    private double amount;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        amount = .0;
        
        cancelBtn.setOnAction(e -> {
            Stage stage = (Stage) cancelBtn.getScene().getWindow();
            stage.close();
        });
        
        amountTextField.textProperty().addListener((e, oldV, newV) -> {
            if (!newV.equals("") && !newV.equals(oldV)) {
                try {
                    amount = Double.parseDouble(newV);
                    System.out.println("Cantidad: " + amount);
                } catch(Exception ex) {
                    System.err.println(ex.getMessage());
                }
            }
        });
        
    }    
    
    public void setActionAndCurrency(String accion, String currency) {
        this.accion = accion;
        this.currency = currency;
        
        actionLabel.textProperty().set("Introduce la cantidad a " + this.accion);
    }
    
    public double getAmount() {
        return this.amount;
    };
}
