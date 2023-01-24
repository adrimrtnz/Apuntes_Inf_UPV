using Magazine.Entities;

using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace MagazineObjectDesignTests
{
    
    [TestClass]
    public class MagazineTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {
            PropertyInfo property = typeof(Magazine.Entities.Magazine).GetProperty("Areas");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Areas property should be declared virtual.");
            property = typeof(Magazine.Entities.Magazine).GetProperty("Issues");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Issues property should be declared virtual.");
            property = typeof(Magazine.Entities.Magazine).GetProperty("ChiefEditor");
            Assert.IsTrue(property.GetMethod.IsVirtual, "ChiefEditor property should be declared virtual.");


        }
        [TestMethod]
        public void NoParamsConstructorInitializesMaintenances()
        {
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine();
            Assert.AreNotSame(null, magazine, "There must be a constructor without parameters.");
            Assert.IsNotNull(magazine.Areas, "Collection of Areas not properly initialized. \n Patch the problem adding:  Areas = new List<Area>();");
            Assert.IsNotNull(magazine.Issues, "Collection of Issues not properly initialized. \n Patch the problem adding:  Issues = new List<Issues>();");

            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, magazine.Areas.Count, "Collection of Areas not properly initialized. \n The list should be empty\n");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, magazine.Issues.Count, "Collection of Issues not properly initialized. \n The list should be empty\n");

        }

        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, TestData.EXPECTED_MAGAZINE_CHIEFEDITOR);

            Assert.AreEqual(TestData.EXPECTED_MAGAZINE_NAME, magazine.Name, "Name not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_MAGAZINE_CHIEFEDITOR, magazine.ChiefEditor, " not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.IsNotNull(magazine.Areas, "Collection of Areas not properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");
            Assert.IsNotNull(magazine.Issues, "Collection of Issues not properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");

        }

    }
}
