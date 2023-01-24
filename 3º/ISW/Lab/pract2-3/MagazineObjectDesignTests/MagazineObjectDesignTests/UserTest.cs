using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Reflection;
using Magazine.Entities;

namespace MagazineObjectDesignTests
{
    [TestClass]
    public class UserTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {
            PropertyInfo property = typeof(User).GetProperty("MainAuthoredPapers");
            Assert.IsTrue(property.GetMethod.IsVirtual, "MainAuthoredPapers property should be declared virtual.");
            property = typeof(User).GetProperty("Area");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Area property should be declared virtual.");
            property = typeof(User).GetProperty("Magazine");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Magazine property should be declared virtual.");
        }
        [TestMethod]
        public void NoParamsConstructorInitializesCollections()
        {
            User user = new User();
            Assert.AreNotSame(null, user, "There must be a constructor without parameters.");
            Assert.IsNotNull(user.MainAuthoredPapers, "Collection of MainAuthoredPapers not properly initialized. \n Patch the problem adding:  MainAuthoredPapers = new List<Paper>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, user.MainAuthoredPapers.Count, "Collection of MainAuthoredPapers not properly initialized. \n The list should be empty\n");

            Assert.IsNotNull(user.CoAuthoredPapers, "Collection of CoAuthoredPapers not properly initialized. \n Patch the problem adding:  User constructor must call base() Person constructor");
            


        }

        [TestMethod]
        public void ConstructorInitializesProps()
        {
            User user = new User(TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);
            Assert.AreEqual(TestData.EXPECTED_PERSON_ID, user.Id, "Id not properly initialized. Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, user.Name, "Name not properly initialized. Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_SURNAME, user.Surname, "Surname not properly initialized. Please check if you have called the constructor of the parent class by calling base(), and whether you have correctly assigned the parameters in the corresponding class.");
            Assert.IsNotNull(user.CoAuthoredPapers, "Collection of PapersAuthor no properly initialized. \n Patch the problem in the parent class (Person) by adding: PapersAuthor = new List<Paper>();");           
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, user.CoAuthoredPapers.Count, "Collection of PaperAuthor not properly initialized in constructor of the parent class (Person). \n The list should be empty\n");

            Assert.AreEqual(TestData.EXPECTED_USER_ALERTED, user.Alerted, "Alerted not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class");
            Assert.AreEqual(TestData.EXPECTED_USER_AREASOFINTEREST, user.AreasOfInterest, "AreasOfInterest not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class");
            Assert.AreEqual(TestData.EXPECTED_USER_EMAIL, user.Email, "Email not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class");
            Assert.AreEqual(TestData.EXPECTED_USER_LOGIN, user.Login, "Login not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class");
            Assert.AreEqual(TestData.EXPECTED_USER_PASSWORD, user.Password, "Password not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class");

            Assert.IsNotNull(user.MainAuthoredPapers, "Collection of MainAuthoredPapers not properly initialized. \n Patch the problem adding:  MainAuthoredPapers = new List<Paper>(); to the constructor with parameters");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, user.MainAuthoredPapers.Count, "Collection of MainAuthoredPapers not properly initialized. \n The list should be empty\n");
            Assert.AreEqual(null, user.Area, "Area not properly initialized. Please check whether it is nullable or not.");
            Assert.AreEqual(null, user.Magazine, "Magazine not properly initialized. Please check whether it is nullable or not");

            Assert.IsNotNull(user.CoAuthoredPapers, "Collection of CoAuthoredPapers not properly initialized. \n Patch the problem adding:  User constructor must call base() Person constructor");
        }
    }
}
