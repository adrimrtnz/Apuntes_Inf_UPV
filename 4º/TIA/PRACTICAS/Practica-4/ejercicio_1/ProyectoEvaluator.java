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
		double riesgo = 0;
		int aumentar_riesgo = 0;
		int decrementar_riesgo = 0;
		ArrayList<Integer> empresasRiesgo = new ArrayList<Integer>();
		ArrayList<Integer> empresasBajaRiesgo = new ArrayList<Integer>();
		
		// Empresas que aumentan el riesgo
		empresasRiesgo.add(20);
		empresasRiesgo.add(21);
		
		// Empresas que bajan el riesgo
		empresasBajaRiesgo.add(22);
		empresasBajaRiesgo.add(23);
		
		for (int id = 0; id < fenotype.size(); id++)
		{			
			beneficio += fenotype.get(id) * DatosInversiones.beneficioEmpresa[id];
			if (fenotype.get(id) > 0) {				
				riesgo += DatosInversiones.riesgoEmpresa[id];
				if (empresasRiesgo.contains(id)) {
					aumentar_riesgo++;
				} else if (empresasBajaRiesgo.contains(id)) {
					decrementar_riesgo++;
				}
			}
		}
		
		if (aumentar_riesgo == empresasRiesgo.size()) {
			riesgo = riesgo * 1.02;
		}
		
		if (decrementar_riesgo == empresasBajaRiesgo.size()) {
			riesgo = riesgo * 0.97;
		}
		
		// Maximizar el beneficio económico
		Objectives objectives = new Objectives();
		objectives.add("MAX Beneficio económico esperado", Sign.MAX, beneficio * 100);
		objectives.add("MIN Riesgo", Sign.MIN, riesgo/2);
		
		return objectives;
	}
}
