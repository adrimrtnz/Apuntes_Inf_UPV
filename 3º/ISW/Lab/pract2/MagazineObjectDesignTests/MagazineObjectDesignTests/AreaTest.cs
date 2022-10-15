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
    public class AreaTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {
            PropertyInfo property = typeof(Area).GetProperty("Papers");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Papers property should be declared virtual.");
            property = typeof(Area).GetProperty("EvaluationPending");
            Assert.IsTrue(property.GetMethod.IsVirtual, "EvaluationPending property should be declared virtual.");
            property = typeof(Area).GetProperty("PublicationPending");
            Assert.IsTrue(property.GetMethod.IsVirtual, "PublicationPending property should be declared virtual.");
            property = typeof(Area).GetProperty("Magazine");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Magazine property should be declared virtual.");

        }
        [TestMethod]
        public void NoParamsConstructorInitializesCollections()
        {
            Area area = new Area();
            Assert.AreNotSame(null, area, "There must be a constructor without parameters.");
            Assert.IsNotNull(area.Papers, "Collection of Papers not properly initialized. \n Patch the problem adding:  Papers = new List<Paper>();");
            Assert.IsNotNull(area.EvaluationPending, "Collection of EvaluationPending not properly initialized. \n Patch the problem adding:  EvaluationPending = new List<Paper>();");
            Assert.IsNotNull(area.PublicationPending, "Collection of PublicationPending not properly initialized. \n Patch the problem adding:  PublicationPending = new List<Paper>();");
            
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, area.Papers.Count, "Collection of Papers not properly initialized. \n The list should be empty\n");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, area.EvaluationPending.Count, "Collection of EvaluationPending not properly initialized. \n The list should be empty\n");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, area.PublicationPending.Count, "Collection of PublicationPending not properly initialized. \n The list should be empty\n");

        }

        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Area area = new Area(TestData.EXPECTED_AREA_NAME, TestData.EXPECTED_AREA_EDITOR, TestData.EXPECTED_AREA_MAGAZINE);
            
            Assert.AreEqual(TestData.EXPECTED_AREA_NAME, area.Name, "Name not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_AREA_EDITOR, area.Editor, "Editor not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_AREA_MAGAZINE, area.Magazine, "Magazine not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
           
            Assert.IsNotNull(area.Papers, "Collection of Papers not properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");
            Assert.IsNotNull(area.EvaluationPending, "Collection of EvaluationPending not properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");
            Assert.IsNotNull(area.PublicationPending, "Collection of PublicationPending not properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");
        }
    }
}
