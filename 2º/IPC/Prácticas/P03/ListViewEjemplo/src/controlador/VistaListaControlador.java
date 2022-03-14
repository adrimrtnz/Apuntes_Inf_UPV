package controlador;

import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

import modelo.Persona;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.beans.value.ObservableValue;
import modelo.PersonListCell;

public class VistaListaControlador implements Initializable {
	
	
    @FXML private ListView<Persona> vistadeListafxID;
    @FXML private TextField textFieldfxID;
    @FXML private TextField textFieldApellidofxID;

    @FXML private Button BAddfxID;
    @FXML private Button BBorrarfxID;
    @FXML
    private Button BModificarfxID;
    
    @FXML void addAccion(ActionEvent event) {
        // añade a la colección si los campos no son vacíos y no contienen únicamente blancos
         if ((!textFieldfxID.getText().isEmpty())
        	&& (textFieldfxID.getText().trim().length()!=0)
        	&& (!textFieldApellidofxID.getText().isEmpty())
        	&& (textFieldApellidofxID.getText().trim().length()!=0))
         { 
           datos.add(new Persona(textFieldfxID.getText(),textFieldApellidofxID.getText()));
           textFieldfxID.clear();
           textFieldApellidofxID.clear();
           textFieldfxID.requestFocus();  //cambio del foco al textfield.
        	 
         } 
         
    }

    @FXML void borrarAccion(ActionEvent event) {
    	int i = vistadeListafxID.getSelectionModel().getSelectedIndex();
    	if (i>=0) datos.remove(i);
    }
	
	private ObservableList<Persona> datos = null; // Colecci�n vinculada a la vista.
	
	

	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {
            
                // en el código de inicialización del controlador
               

		// TODO Auto-generated method stub
		ArrayList<Persona> misdatos = new ArrayList<Persona>();
		misdatos.add(new Persona("Pepe", "García"));
		misdatos.add(new Persona("María", "Pérez"));
		datos = FXCollections.observableArrayList(misdatos);
		vistadeListafxID.setItems(datos); // vinculaci�n entre la vista y el modelo
                vistadeListafxID.setCellFactory(c -> new PersonListCell());
		
		
		
		// inhabilitar botones al arrancar.
		BAddfxID.setDisable(true);
		BBorrarfxID.setDisable(true);
		// oyente de foco para el textfield.
		textFieldfxID.focusedProperty().addListener((ObservableValue<? extends Boolean> arg2, Boolean antiguo, Boolean nuevo) -> {
                    // TODO Auto-generated method stub
                    if (textFieldfxID.isFocused()) {
                        BAddfxID.setDisable(false);
                        BBorrarfxID.setDisable(true);
                    }
                });
		
		// oyente de foco para el listView
		vistadeListafxID.focusedProperty().addListener((ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) -> {
                    if (vistadeListafxID.isFocused()) {
                        BBorrarfxID.setDisable(false);
                        BAddfxID.setDisable(true);
                    }
                });
                
               

		
	}     

    @FXML
    private void modAccion(ActionEvent event) {
        
    }
        
}
