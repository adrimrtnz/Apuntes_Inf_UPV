/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlapplication;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleButton;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

/**
 *
 * @author jsoler
 */
public class FXMLDocumentController implements Initializable {
    
    @FXML
    private Circle circleFigure;
    @FXML
    private GridPane pane;
    @FXML
    private ToggleButton toggleButton;
    @FXML
    private Slider slider;
    @FXML
    private ColorPicker colorPicker;
    private Color myColor;
    
    //=========================================================  
    
    
    @FXML
    private void handleKeyPressed(KeyEvent event) {
        
        int row = GridPane.getRowIndex(circleFigure);
        int column = GridPane.getColumnIndex(circleFigure);
        
        if(event.getCode() == KeyCode.UP) {
            GridPane.setRowIndex(circleFigure, rowNorm(pane, row - 1));
        }
        else if(event.getCode() == KeyCode.DOWN) {
            GridPane.setRowIndex(circleFigure, rowNorm(pane, row + 1));
        }
        else if(event.getCode() == KeyCode.LEFT) {
            GridPane.setColumnIndex(circleFigure, columnNorm(pane, column - 1));
        }
        else if(event.getCode() == KeyCode.RIGHT) {
            GridPane.setColumnIndex(circleFigure, columnNorm(pane, column + 1));
        }
        
        event.consume();
    }
    
    @FXML
    private void handleMousePressed(MouseEvent event) {
        double x = event.getSceneX();
        double y = event.getSceneY();
        //System.out.println("Mouse PRESSED: (x: " + x + ",y: " + y + ")");
        
        GridPane.setConstraints(circleFigure, columnCalc(pane, x), rowCalc(pane, y));
        event.consume();
    }
    
    @FXML
    private void handleMouseDragged(MouseEvent event) {
        double initialX = circleFigure.getLayoutX();
        double initialY = circleFigure.getLayoutY();
        
        circleFigure.setTranslateX(event.getSceneX() - initialX);
        circleFigure.setTranslateY(event.getSceneY() - initialY);
        
        event.consume();
    }
    
    @FXML
    private void handleMouseReleased(MouseEvent event) {
        double x = event.getSceneX();
        double y = event.getSceneY();
        
        circleFigure.setTranslateX(0);
        circleFigure.setTranslateY(0);
        
        GridPane.setConstraints(circleFigure, columnCalc(pane, x), rowCalc(pane, y));
        
        event.consume();
    }

    
    private int rowNorm(GridPane grid, int row) {
        int rowCount = grid.getRowCount();
        return (row + rowCount) % rowCount;
    }
    
    private int columnNorm(GridPane grid, int column) {
        int columnCount = grid.getColumnCount();
        return (column + columnCount) % columnCount;
    }
    
    public int rowCalc(GridPane grid, double y) {
        int rowWidth = (int)grid.getWidth() / grid.getRowCount();
        return (int) (y / rowWidth);
    }
    
    public int columnCalc(GridPane grid, double x) {
        int celdaWidth = (int)grid.getWidth() / grid.getColumnCount();
        return (int) (x / celdaWidth);
    }
    
    //=========================================================
    // you must initialize here all related with the object 
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        circleFigure.scaleXProperty().bind(slider.valueProperty());
        circleFigure.scaleYProperty().bind(slider.valueProperty());
        circleFigure.fillProperty().bind(colorPicker.valueProperty());  
    }    

    @FXML
    private void handleToggleButton(ActionEvent event) {
        if (toggleButton.isSelected()) {
            myColor = colorPicker.getValue();
            colorPicker.setValue(Color.TRANSPARENT);
            circleFigure.setStroke(myColor);
            circleFigure.setStrokeWidth(3);
        }
        else {
            colorPicker.setValue(myColor);
            circleFigure.setStroke(Color.BLACK);
            circleFigure.setStrokeWidth(1);
        }
        event.consume();
    }
}
