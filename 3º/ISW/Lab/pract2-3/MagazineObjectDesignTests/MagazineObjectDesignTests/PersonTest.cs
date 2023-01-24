using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Reflection;
using Magazine.Entities;

namespace MagazineObjectDesignTests
{
    [TestClass]
    public class PersonTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {
            PropertyInfo property = typeof(Person).GetProperty("CoAuthoredPapers");
            Assert.IsTrue(property.GetMethod.IsVirtual, "CoAuthoredPapers property should be declared virtual.");
        }
        [TestMethod]
        public void NoParamsConstructorInitializesCollections()
        {
            Person person = new Person();
            Assert.AreNotSame(null, person, "There must be a constructor without parameters.");
            Assert.IsNotNull(person.CoAuthoredPapers, "Collection of CoAuthoredPapers not properly initialized. \n Patch the problem adding:  CoAuthoredPapers = new List<Paper>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, person.CoAuthoredPapers.Count, "Collection of CoAuthoredPapers not properly initialized. \n The list should be empty\n");
        }

        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Person person = new Person(TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_SURNAME);
            Assert.AreEqual(TestData.EXPECTED_PERSON_ID, person.Id, "Id not properly initialized.Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, person.Name, "Name not properly initialized. Please check if you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_SURNAME, person.Surname, "Surname not properly initialized. Please check if you have correctly assigned the parameters in the corresponding class.");

            Assert.IsNotNull(person.CoAuthoredPapers, "Collection of CoAuthoredPapers no properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, person.CoAuthoredPapers.Count, "Collection of CoAuthoredPapers not properly initialized. \n The list should be empty\n");
           
        }
    }
}
