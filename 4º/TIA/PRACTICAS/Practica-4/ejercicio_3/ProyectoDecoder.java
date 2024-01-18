package proyecto;

import java.util.ArrayList;

import org.opt4j.core.genotype.DoubleGenotype;
import org.opt4j.core.problem.Decoder;

public class ProyectoDecoder implements Decoder<DoubleGenotype, ArrayList<Double>>
{
	@Override
	public ArrayList<Double> decode(DoubleGenotype genotype)
	{
		ArrayList<Double> fenotype = new ArrayList<Double>();
		
		// Copiamos los valores del DoubleGenotype en la colección
		for (int id = 0; id < genotype.size(); id++)
		{
			fenotype.add(genotype.get(id));
		}
		
		fenotype = reparar(fenotype);
		
		return fenotype;
	}
	
	
	private ArrayList<Double> reparar(ArrayList<Double> fenotype) {
		// Método para corregir fenotipos que no cumplan ciertas condiciones
		double capacidad = DatosInversiones.maxInversionTotal;
		
		/*
		 * La estrategia es, mientras no sobrepase el maxInversion, todo ok
		 * En el momento en el que pase, a ese individuo se le asigna la capacidad
		 * restante y al resto 0
		 * */
		
		// E21 tiene que ser la suma de las inversiones en E1 y E2
		double inversionE21 = fenotype.get(0) + fenotype.get(1);
		fenotype.set(20, inversionE21);
		
		for (int id = 0; id < fenotype.size(); id++) {
			double exp = fenotype.get(id);
			if (capacidad - exp < 0) {
				fenotype.set(id, capacidad);
				capacidad = 0;
				
				// Si no podemos invertir la cantidad necesaria en E21, 
				// se corrige al individuo poniendo la inversión de E1, 
				// E2 y E21 poniendolas a 0
				if (id == 20) {
					fenotype.set(0, 0.0);
					fenotype.set(1, 0.0);
					fenotype.set(20, 0.0);
				}
			} 
			else {
				capacidad -= exp;
			}
		}
		
		return fenotype;
	}
}
