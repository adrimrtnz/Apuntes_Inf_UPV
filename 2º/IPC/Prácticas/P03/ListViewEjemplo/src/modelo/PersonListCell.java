/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modelo;

import javafx.scene.control.ListCell;

/**
 *
 * @author Adrián Martínez
 */
public class PersonListCell extends ListCell<Persona> 
{
    @Override
    protected void updateItem(Persona item, boolean empty) {
        super.updateItem(item, empty);
        
        if (item == null || empty) {
            setText(null);
        }
        else {   
            setText(item.getApellidos() + ", " + item.getNombre());
        }
    }
    /*
    Override
    public void initialize(URL url, ResourceBundle rb) {
        ArrayList<Persona> backupList = new ArrayList<>();
        
    } 
*/
}
