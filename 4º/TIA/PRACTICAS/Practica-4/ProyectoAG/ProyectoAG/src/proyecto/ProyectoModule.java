package proyecto;

import org.opt4j.core.problem.ProblemModule;

public class ProyectoModule extends ProblemModule 
{

	@Override
	protected void config() 
	{
		// mostrará errores mientras ProyectoCreator, ProyectoDecoder y ProyectoEvaluator no estén completos
		bindProblem(ProyectoCreator.class, ProyectoDecoder.class, ProyectoEvaluator.class);
	}

}
