package proyecto;

import org.opt4j.core.problem.ProblemModule;

public class ProyectoModule extends ProblemModule 
{
	@Override
	protected void config() 
	{
		// mostrar� errores mientras ProyectoCreator, ProyectoDecoder y ProyectoEvaluator no est�n completos
		bindProblem(ProyectoCreator.class, ProyectoDecoder.class, ProyectoEvaluator.class);
	}

}
