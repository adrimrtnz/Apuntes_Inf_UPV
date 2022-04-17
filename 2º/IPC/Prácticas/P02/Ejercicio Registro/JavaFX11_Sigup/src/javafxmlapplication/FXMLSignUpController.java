/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlapplication;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.binding.Bindings;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;


/**
 *
 * @author svalero
 */
public class FXMLSignUpController implements Initializable {


 
    //properties to control valid fieds values. 
    private BooleanProperty validPassword;
    private BooleanProperty validEmail;
    private BooleanProperty equalPasswords;  

    private BooleanProperty validFields;
    
    //When to strings are equal, compareTo returns zero
    private final int EQUALS = 0;  
    @FXML
    private Button accept_btn;
    @FXML
    private Button cancel_btn;
    @FXML
    private TextField usser_email;
    @FXML
    private Label incEmailLabel;
    @FXML
    private PasswordField usser_password;
    @FXML
    private PasswordField rep_password;
    @FXML
    private Label incRepPassLabel;
    @FXML
    private Label incPassLabel;
    
   
    

    /**
     * Updates the boolProp to false.Changes to red the background of the edit. 
     * Makes the error label visible and sends the focus to the edit. 
     * @param errorLabel label added to alert the user
     * @param textField edit text added to allow user to introduce the value
     * @param boolProp property which stores if the value is correct or not
     */
    private void manageError(Label errorLabel,TextField textField, BooleanProperty boolProp ){
        boolProp.setValue(Boolean.FALSE);
        showErrorMessage(errorLabel,textField);
        textField.requestFocus();
 
    }
    /**
     * Updates the boolProp to true. Changes the background 
     * of the edit to the default value. Makes the error label invisible. 
     * @param errorLabel label added to alert the user
     * @param textField edit text added to allow user to introduce the value
     * @param boolProp property which stores if the value is correct or not
     */
    private void manageCorrect(Label errorLabel,TextField textField, BooleanProperty boolProp ){
        boolProp.setValue(Boolean.TRUE);
        hideErrorMessage(errorLabel,textField);
        
    }
    /**
     * Changes to red the background of the edit and
     * makes the error label visible
     * @param errorLabel
     * @param textField 
     */
    private void showErrorMessage(Label errorLabel,TextField textField)
    {
        errorLabel.visibleProperty().set(true);
        textField.styleProperty().setValue("-fx-background-color: #FCE5E0");    
    }
    /**
     * Changes the background of the edit to the default value
     * and makes the error label invisible.
     * @param errorLabel
     * @param textField 
     */
    private void hideErrorMessage(Label errorLabel,TextField textField)
    {
        errorLabel.visibleProperty().set(false);
        textField.styleProperty().setValue("");
    }


    

    
    //=========================================================
    // you must initialize here all related with the object 
    @Override
    public void initialize(URL url, ResourceBundle rb) {
       
        validEmail = new SimpleBooleanProperty();
        validPassword = new SimpleBooleanProperty();   
        equalPasswords = new SimpleBooleanProperty();
        
        validPassword.setValue(Boolean.FALSE);
        validEmail.setValue(Boolean.FALSE);
        equalPasswords.setValue(Boolean.FALSE);
        
       
        
        
        BooleanBinding validFields = Bindings.and(validEmail, validPassword)
                 .and(equalPasswords);
        
        usser_email.focusedProperty().addListener((ob,oldValue,newValue) -> {
                if(!newValue) {
                    checkEditEmail();
                }
        });
        
        usser_password.focusedProperty().addListener((ob,oldValue,newValue) -> {
            if(!newValue) {
                checkEditPassword(usser_password, incPassLabel);
                //checkEqualPasswords();
            }
        
        });
        
        rep_password.focusedProperty().addListener((ob,oldValue,newValue) -> {
            if(!newValue) {
                checkEqualPasswords();
            }
        
        });
        

    } 
    
    public void checkEditEmail() {
        if(!Utils.checkEmail(usser_email.textProperty().getValueSafe())) {
            manageError(incEmailLabel, usser_email, validEmail);
        }
        else {
            manageCorrect(incEmailLabel, usser_email, validEmail);
        }
    }
    
    public void checkEditPassword(TextField password, Label passLabel) {
        if(!Utils.checkPassword(password.textProperty().getValueSafe())) {
            manageError(passLabel, password, validPassword);
        }
        else {
            manageCorrect(passLabel, password, validPassword);
        }
    }
    
    public void checkEqualPasswords() {
        if (usser_password.textProperty().getValueSafe().compareTo(
        rep_password.textProperty().getValueSafe()) != EQUALS) {
            manageError(incRepPassLabel, rep_password, equalPasswords);
        }
        else {
            manageCorrect(incRepPassLabel, rep_password, equalPasswords);
        }
    }
}