/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlapplication;

import java.net.URL;
import java.util.ArrayList;
import java.util.Collections;
import java.util.ResourceBundle;
import java.util.Set;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Adrián Martínez
 */
public class FXML_amarmar4Controller implements Initializable {

    @FXML
    private Button addBtn;
    @FXML
    private Button upBtn;
    @FXML
    private Button downBtn;
    @FXML
    private ListView<String> listView;
    
    private ObservableList<String> datos = null;
    @FXML
    private TextField textField;
    @FXML
    private Button clearBtn;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        ArrayList<String> cadenas = new ArrayList<>();
        datos = FXCollections.observableArrayList(cadenas);
        listView.setItems(datos);
        
        upBtn.disableProperty().set(true);
        downBtn.disableProperty().set(true);
        
        addBtn.disableProperty().bind(textField.textProperty().isEmpty());

        addBtn.setOnAction(e -> {
            datos.add(textField.getText());
            textField.textProperty().set("");
        });
        
        textField.focusedProperty().addListener((e,oldV, newV )-> {
            if(newV) {
                listView.getSelectionModel().select(-1);
            }
        });
        
        listView.getSelectionModel().selectedIndexProperty().addListener((e, oldV, newV) -> {
            
            if((int)newV > 0 && (int)newV < datos.size() - 1) {
                upBtn.disableProperty().set(false);
                downBtn.disableProperty().set(false);
            }
            else if((int)newV < datos.size() - 1 && (int)newV != -1) {
                upBtn.disableProperty().set(true);
                downBtn.disableProperty().set(false);
            }
            else if ((int)newV > 0) {
                downBtn.disableProperty().set(true);
                upBtn.disableProperty().set(false);
            }
            else {
                upBtn.disableProperty().set(true);
                downBtn.disableProperty().set(true);
            }
        });
        
        
        upBtn.setOnAction(e -> {
            int index = listView.getSelectionModel().getSelectedIndex();
            Collections.swap(datos, index - 1, index);
            listView.getSelectionModel().select(index - 1);
        });
        
        downBtn.setOnAction(e -> {
            int index = listView.getSelectionModel().getSelectedIndex();
            Collections.swap(datos, index, index + 1);
            listView.getSelectionModel().select(index + 1);
        });
    }    

    @FXML
    private void loadAboutScreen(ActionEvent event) throws Exception {
        FXMLLoader aboutScreen = new FXMLLoader(getClass().getResource("AboutScreenView_amarmar4.fxml"));
        Parent root = aboutScreen.load();
        
        Scene scene = new Scene(root);
        Stage stage = new Stage();
        stage.setTitle("About");
        stage.setScene(scene);
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.showAndWait();
    }

    @FXML
    private void clearAction(ActionEvent event) {
        datos.clear();
    }
    
    public void focusClearBtn() {
        clearBtn.requestFocus();
    }
    
}
