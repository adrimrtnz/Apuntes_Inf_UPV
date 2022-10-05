using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Ejercicio2
{
    public class ClassA
    {
        private String a1;
        private String a2;

        public ICollection<ClassC> C
        {
            get;
            set;
        }

        public ICollection<ClassE> E {
            get;
            set;
        }
    }
}