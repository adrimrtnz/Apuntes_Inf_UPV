/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package demointernacionalizacion;

import java.util.Locale;
import java.util.ResourceBundle;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 * @author Juan
 */
public class DemoInternacionalizacion extends Application {
    
    @Override
    public void start(Stage stage) throws Exception {
        
        
        
        ResourceBundle bundle = ResourceBundle.getBundle("recursos.cadenas", new Locale("es","ES"));
        // Pasar el bundle al FXMLLoader
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"), bundle);
        
        Scene scene = new Scene(root);
        stage.setTitle(bundle.getString("stage.titulo"));
        stage.setScene(scene);
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
