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
		for (int id = 0; id < fenotype.size(); id++) {
			double exp = fenotype.get(id);
			if (capacidad - exp < 0) {
				fenotype.set(id, capacidad);
				capacidad = 0;
			} 
			else {
				capacidad -= exp;
			}
		}
		
		return fenotype;
	}
}
