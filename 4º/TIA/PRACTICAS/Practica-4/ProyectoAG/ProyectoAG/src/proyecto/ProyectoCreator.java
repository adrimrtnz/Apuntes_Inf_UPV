package proyecto;

import java.util.Random;

import org.opt4j.core.genotype.DoubleGenotype;
import org.opt4j.core.problem.Creator;

public class ProyectoCreator implements Creator<DoubleGenotype>
{
	public DoubleGenotype create()
	{
		DoubleGenotype genotype = new DoubleGenotype(
				DatosInversiones.minInversionPorEmpresa, 
				DatosInversiones.maxInversionPorEmpresa);
		genotype.init(new Random(), DatosInversiones.numEmpresas);
		return genotype;
	}
}
