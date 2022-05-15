/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlapplication;

import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.CheckMenuItem;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.RadioMenuItem;
import javafx.scene.control.ToggleGroup;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Adrián Martínez
 */
public class FXML_amarmar4Controller implements Initializable {

    @FXML private Label stateLabel;
    @FXML private Label currencyLabel;
    @FXML
    private RadioMenuItem bitcoinBtn;
    @FXML
    private ToggleGroup currencies;
    @FXML
    private RadioMenuItem etherBtn;
    @FXML
    private RadioMenuItem latecoinBtn;

    
    private String baseState;
    private String currency;
    private ToggleGroup group;
    private ObservableList<String> datos;
    @FXML
    private ListView<String> listView;
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        baseState = "(Nombre, Apellido, DNI) Selected: ";
        
        stateLabel.textProperty().set(baseState + "BitCoin");
        
        group = bitcoinBtn.getToggleGroup();
        group.selectToggle(bitcoinBtn);
        group.selectedToggleProperty().addListener((e, oldV, newV) -> {
            if(!newV.equals(oldV)) {
                currencyLabel.textProperty().set( ((RadioMenuItem) group.getSelectedToggle()).textProperty().get() );
            }
        });
        
        ArrayList<String> monedero = new ArrayList<>();
        datos = FXCollections.observableArrayList(monedero);
        listView.setItems(datos);
    }    

    @FXML
    private void comprar(ActionEvent event) throws Exception {
        FXMLLoader comprar = new FXMLLoader(getClass().getResource("CompraCryptoView.fxml"));
        Parent root = comprar.load();
        
        CompraCryptoController controlador = comprar.getController();
        controlador.setActionAndCurrency("comprar", currencyLabel.getText());
        
        Scene scene = new Scene(root);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.setTitle("Comprar");
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.showAndWait();
        
        double amount = controlador.getAmount();
        datos.add(currencyLabel.getText() + ": " + amount);
    }

    @FXML
    private void vender(ActionEvent event) throws Exception {
        FXMLLoader comprar = new FXMLLoader(getClass().getResource("CompraCryptoView.fxml"));
        Parent root = comprar.load();
        
        CompraCryptoController controlador = comprar.getController();
        controlador.setActionAndCurrency("vender", currencyLabel.getText());
        
        Scene scene = new Scene(root);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.setTitle("Vender");
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.showAndWait();
    }
    
    
}
