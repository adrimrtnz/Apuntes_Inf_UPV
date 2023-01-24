using Magazine.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Magazine.Persistence;

namespace MagazinePersistenceTests
{

    [TestClass]
    public class MagazineTest : BaseTest
    {

        [TestMethod]
        public void StoresInitialData()
        {
            User chiefEditor = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);

            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chiefEditor);

            dal.Insert(magazine);
            dal.Commit();

            Magazine.Entities.Magazine magazineDAL = dal.GetAll<Magazine.Entities.Magazine>().First();
            Assert.AreEqual(TestData.EXPECTED_MAGAZINE_NAME, magazineDAL.Name, "Magazine not properly stored.");

            Assert.AreEqual(chiefEditor, magazineDAL.ChiefEditor, "ChiefEditor not properly stored.");

            Assert.IsNotNull(magazineDAL.Issues, "Collection of Issues not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, magazineDAL.Issues.Count, "Collection of Issues not properly initialized. \n The list should be empty\n");

            Assert.IsNotNull(magazineDAL.Areas, "Collection of Areas not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, magazineDAL.Areas.Count, "Collection of Areas not properly initialized. \n The list should be empty\n");

        }

        [TestMethod]
        public void StoresDataWithRelations()
        {

            User chiefEditor1 = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chiefEditor1);
            chiefEditor1.Magazine = magazine;

            User editor1 = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);
            Area area1 = new Area(TestData.EXPECTED_AREA_NAME, editor1, magazine);
            editor1.Area = area1;
            Issue issue1 = new Issue(TestData.EXPECTED_ISSUE_NUMBER, magazine);

            magazine.Areas.Add(area1);
            magazine.Issues.Add(issue1);

            dal.Insert(magazine);
            dal.Commit();

            Magazine.Entities.Magazine magazineDAL = dal.GetAll<Magazine.Entities.Magazine>().First();
            Assert.AreEqual(TestData.EXPECTED_MAGAZINE_NAME, magazineDAL.Name, "Magazine not properly stored.");

            Assert.AreEqual(chiefEditor1, magazineDAL.ChiefEditor, "ChiefEditor not properly stored.");


            Assert.IsNotNull(magazineDAL.Areas, "Collection of Areas not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, magazineDAL.Areas.Count, "Collection of Areas not properly initialized. \n The list should have one element\n");
            Assert.AreEqual(area1, magazineDAL.Areas.FirstOrDefault(), "Areas relationship not properly created.");
            Assert.IsNotNull(magazineDAL.Issues, "Collection of Issues not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, magazineDAL.Issues.Count, "Collection of Issues not properly initialized. \n The list should have one element\n");
            Assert.AreEqual(issue1, magazineDAL.Issues.FirstOrDefault(), "Issues relationship not properly created.");
        }
    }
}

