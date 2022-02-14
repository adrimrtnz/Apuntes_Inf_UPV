package com.ipc.calculadora;

import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

public class CalculatorController {
    
    @FXML
    private enum operations {
        SUM, SUB, MULT, DIV
    }
    
    @FXML
    private int operation;
    
    @FXML
    private TextField calcText;
    
    private double firstNumber = 0;
    private double secondNumber = 0;
    private double result = 0;
    private boolean canAddDecimalPoint = true;
    
    @FXML
    public void getNumber(ActionEvent event) {
        if (calcText.getText().equals("0")) {
            calcText.setText(((Button)event.getSource()).getText());
        }
        else {
            calcText.setText(calcText.getText() +  ((Button)event.getSource()).getText());
        }
    }
    
    public void addDecimalPoint (ActionEvent event) {
        if (canAddDecimalPoint) {
            calcText.setText(calcText.getText() +  ((Button)event.getSource()).getText());
            canAddDecimalPoint = false;
        }
        else { return; }
    }
    
    @FXML
    public void sum(ActionEvent event) {
        operation = operations.SUM.ordinal();
        
        firstNumber = new Double(calcText.getText());
        calcText.setText("");
        canAddDecimalPoint = true;
    }
    
    @FXML
    public void sub(ActionEvent event) {
        operation = operations.SUB.ordinal();
        
        firstNumber = new Double(calcText.getText());
        calcText.setText("");
        canAddDecimalPoint = true;
    }
    
    @FXML
    public void divide(ActionEvent event) {
        operation = operations.DIV.ordinal();
        
        firstNumber = new Double(calcText.getText());
        calcText.setText("");
        canAddDecimalPoint = true;
    }
    
    @FXML
    public void multiply(ActionEvent event) {
        operation = operations.MULT.ordinal();
        
        firstNumber = new Double(calcText.getText());
        calcText.setText("");
        canAddDecimalPoint = true;
    }
    
    @FXML
    public void getResult(ActionEvent event) {
        secondNumber = new Double(calcText.getText());
        canAddDecimalPoint = true;
        
        switch(operation) {
            case 0:
                firstNumber = firstNumber + secondNumber;
                result = firstNumber;
                
                calcText.setText(Double.toString(result));
                break;
                
            case 1:
                firstNumber = firstNumber - secondNumber;
                result = firstNumber;
                
                calcText.setText(Double.toString(result));
                break;
                
            case 2:
                firstNumber = firstNumber * secondNumber;
                result = firstNumber;
                
                calcText.setText(Double.toString(result));
                break;
            
            case 3:
                firstNumber = firstNumber / secondNumber;
                result = firstNumber;
                
                calcText.setText(Double.toString(result));
                break;
        }
    }
    
    @FXML
    public void reset(ActionEvent event) {
        firstNumber = 0;
        secondNumber = 0;
        result = 0;
        canAddDecimalPoint = true;
        calcText.setText("0");
    }
}