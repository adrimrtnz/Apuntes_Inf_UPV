using Magazine.Entities;
using Magazine.Persistence;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;

namespace MagazinePersistenceTests
{
   [TestClass]
    public class PersonTest: BaseTest
    {
        [TestMethod]
        public void StoresInitialData()
        {
            Person person = new Person(TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_SURNAME);
            dal.Insert(person);
            dal.Commit();

            Person personDAL = dal.GetAll<Person>().First();
            Assert.AreEqual(TestData.EXPECTED_PERSON_ID, personDAL.Id, "Id not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, personDAL.Name, "Name not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_SURNAME, personDAL.Surname, "Surmane not properly stored.");

            Assert.IsNotNull(personDAL.CoAuthoredPapers, "Collection of CoAuthoredPapers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, personDAL.CoAuthoredPapers.Count, "Collection of CoAuthoredPapers not properly initialized. \n The list should be empty\n");

        }

        [TestMethod]
        public void StoresDataWithRelations()
        {

            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);

            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);
            Person person = new Person(TestData.EXPECTED_PERSON_ID, TestData.EXPECTED_PERSON_NAME, TestData.EXPECTED_PERSON_SURNAME);
            User author = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);
            Paper paper = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, area, author);

           
            person.CoAuthoredPapers.Add(paper);
            paper.CoAuthors.Add(person);

            dal.Insert(person);
            dal.Commit();


            Person personDAL = dal.GetAll<Person>().First();
            Assert.AreEqual(TestData.EXPECTED_PERSON_ID, personDAL.Id, "Id not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_NAME, personDAL.Name, "Name not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_PERSON_SURNAME, personDAL.Surname, "Surname not properly stored.");

            Assert.IsNotNull(personDAL.CoAuthoredPapers, "Collection of CoAuthoredPapers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, personDAL.CoAuthoredPapers.Count, "Collection of CoAuthoredPapers not properly initialized. \n The list should have one element\n");
            Assert.AreEqual(paper, personDAL.CoAuthoredPapers.FirstOrDefault(), "CoAuthoredPapers relationship not properly created.");

        }
    }
}