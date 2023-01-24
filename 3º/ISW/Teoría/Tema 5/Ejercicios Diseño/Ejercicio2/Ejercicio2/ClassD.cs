using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ejercicio2
{
    internal class ClassD
    {
        private String d1;
        private int h1;

        public ICollection<ClassC> C
        {
            get;
            set;
        }

        public ICollection<ClassG> G
        {
            get;
            set;
        }
    }
}
