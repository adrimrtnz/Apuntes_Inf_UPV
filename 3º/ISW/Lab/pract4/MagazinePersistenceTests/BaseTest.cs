using Magazine.Entities;
using Magazine.Persistence;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;
using System.Reflection;
using System;
using System.ComponentModel.DataAnnotations;

namespace MagazinePersistenceTests
{
    [TestClass]
    public class BaseTest
    {
        protected private EntityFrameworkDAL dal;

        private static bool HasRequiredAnnotation(PropertyInfo property)
        {
            var attributes = property.GetCustomAttributes(false);
            Attribute[] attrs = System.Attribute.GetCustomAttributes(property);
            return attrs.Any((attr) =>
            {
                return attr is RequiredAttribute;
            });

        }

        [TestInitialize]
        public void IniTests()
        {
            // Si no hacemos este test aquí da otra excepción que no es trivial
            // para los alumnos saber qué está ocurriendo
            // Con este assert sabrán que han de añadir el Required
            Assert.IsTrue(HasRequiredAnnotation(typeof(Area).GetProperty("Editor")), "Property named \"Editor\" in \"Area\" class should have Data Annotation [Required]");
            Assert.IsTrue(HasRequiredAnnotation(typeof(Magazine.Entities.Magazine).GetProperty("ChiefEditor")), "Property named \"ChiefEditor\" in \"Magazine\" class should have Data Annotation [Required]");
            dal = new EntityFrameworkDAL(new MagazineDbContext());
            dal.RemoveAllData();
        }
        [TestCleanup]
        public void CleanTests()
        {
            dal.RemoveAllData();
        }
    }
}
