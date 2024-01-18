package proyecto;

import java.util.ArrayList;

import org.opt4j.core.Objective.Sign;
import org.opt4j.core.Objectives;
import org.opt4j.core.problem.Evaluator;

public class ProyectoEvaluator implements Evaluator<ArrayList<Double>>
{
	@Override
	public Objectives evaluate(ArrayList<Double> fenotype)
	{
		double inversion = 0.0;
		double beneficio = 0.0;
		int riesgo = 0;
		
		for (int id = 0; id < fenotype.size(); id++)
		{
//			inversion += fenotype.get(id);
//			if (inversion > DatosInversiones.maxInversionTotal) 
//			{
//				// No se puede invertir más del 100%
//				beneficio = Double.MIN_VALUE;
//				riesgo = Integer.MAX_VALUE;
//				break;
//			}
			
			
			beneficio += fenotype.get(id) * DatosInversiones.beneficioEmpresa[id];
			if (fenotype.get(id) > 0) {				
				riesgo += DatosInversiones.riesgoEmpresa[id];
			}
		}
		
		// Maximizar el beneficio económico
		Objectives objectives = new Objectives();
		objectives.add("MAX Beneficio económico esperado", Sign.MAX, beneficio * 100);
		objectives.add("MIN Riesgo", Sign.MIN, riesgo);
		
		return objectives;
	}
}
