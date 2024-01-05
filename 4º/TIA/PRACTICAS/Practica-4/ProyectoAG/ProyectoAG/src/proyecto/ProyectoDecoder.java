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
		
		return fenotype;
	}
}
