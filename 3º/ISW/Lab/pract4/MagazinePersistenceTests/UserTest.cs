using Magazine.Entities;
using Magazine.Persistence;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;

namespace MagazinePersistenceTests
{
    [TestClass]
    public class UserTest : BaseTest
    {
        
        [TestMethod]
        public void StoresInitialData()
        {
            
            User user = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);
            dal.Insert(user);
            dal.Commit();

            User userDAL = dal.GetAll<User>().First();
            Assert.AreEqual(TestData.EXPECTED_USER_ID, userDAL.Id, "Id not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_NAME, userDAL.Name, "Name not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_SURNAME, userDAL.Surname, "Surname not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_ALERTED, userDAL.Alerted, "Alerted not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_AREASOFINTEREST, userDAL.AreasOfInterest, "AreasOfInterest not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_EMAIL, userDAL.Email, "Email not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_LOGIN, userDAL.Login, "Login not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER_PASSWORD, userDAL.Password, "Password not properly stored.");


            Assert.IsNotNull(userDAL.MainAuthoredPapers, "Collection of MainAuthoredPapers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, userDAL.MainAuthoredPapers.Count, "Collection of MainAuthoredPapers not properly initialized. \n The list should be empty\n");
            Assert.AreEqual(null, userDAL.Area, "Area not properly initialized. Please check whether it is nullable or not.");
            Assert.AreEqual(null, userDAL.Magazine, "Magazine not properly initialized. Please check whether it is nullable or not.");


        }
       
        [TestMethod]
        public void StoresDataWithRelations()
        {
                
            User user = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);

            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);
            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);
            Paper paper = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, area, user);

            user.MainAuthoredPapers.Add(paper);
            dal.Insert(paper);
            dal.Commit();

            User userDAL = dal.GetAll<User>().Where<User>(u=>u.Id.Equals(TestData.EXPECTED_USER2_ID)).FirstOrDefault();
            Assert.AreEqual(TestData.EXPECTED_USER2_ID, userDAL.Id, "Id not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER2_NAME, userDAL.Name, "Name not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_USER2_SURNAME, userDAL.Surname, "Surname not properly stored.");

            Assert.IsNotNull(userDAL.MainAuthoredPapers, "Collection of MainAuthoredPapers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, userDAL.MainAuthoredPapers.Count, "Collection of MainAuthoredPapers not properly initialized. \n The list should have one element\n");
            Assert.AreEqual(paper, userDAL.MainAuthoredPapers.FirstOrDefault(), "MainAuthoredPapers relationship not properly created.");


            userDAL = dal.GetAll<User>().Where<User>(u => u.Id.Equals(editor.Id)).FirstOrDefault();
            Assert.IsNotNull(userDAL.Area, "Area not properly initialized.");
            Assert.AreEqual(userDAL.Area, area, "Area not properly stored.");

            User chiefDAL= dal.GetAll<User>().Where<User>(u => u.Id.Equals(TestData.EXPECTED_CHIEF_ID)).FirstOrDefault();
            Assert.IsNotNull(chiefDAL.Magazine, "Magazine not properly initialized.");
            Assert.AreEqual(chiefDAL.Magazine, magazine, "Magazine not properly stored."); 
        }
    }
}
