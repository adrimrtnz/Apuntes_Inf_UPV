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
			// En la empresa E3 hay que invertir más de un 5%
			if (id == 2 && !(fenotype.get(id) > 5.0) ) {
				// Penalizamos este individuo
				beneficio = Double.MIN_VALUE;
				riesgo = Integer.MAX_VALUE;
				break;
			}
			
			if (fenotype.get(id) > DatosInversiones.margenComision) {
				double beneficio_aux = fenotype.get(id) * DatosInversiones.beneficioEmpresa[id];
				beneficio += beneficio_aux - beneficio_aux*(DatosInversiones.comisiones[id]/100);
			}
			else {
				beneficio += fenotype.get(id) * DatosInversiones.beneficioEmpresa[id];
			}
			

			if (fenotype.get(id) > 0) {				
				riesgo += DatosInversiones.riesgoEmpresa[id];
			}
		}
		
		// Maximizar el beneficio económico
		Objectives objectives = new Objectives();
		objectives.add("MAX Beneficio económico esperado", Sign.MAX, beneficio * 100);
		objectives.add("MIN Riesgo", Sign.MIN, riesgo);
		
		// Maximizar Inversion E20
		objectives.add("MAX Inversion E20", Sign.MAX, fenotype.get(19));
		
		// Minimizar Inversion E4
		objectives.add("MIN Inversion E4", Sign.MIN, fenotype.get(3));
		
		return objectives;
	}
}
