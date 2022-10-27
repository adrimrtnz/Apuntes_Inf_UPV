using Magazine.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MagazinePersistenceTests
{
    [TestClass]
    public class IssueTest : BaseTest
    {
        [TestMethod]
        public void StoresInitialData()
        {
            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            Issue issue = new Issue(TestData.EXPECTED_ISSUE_NUMBER, magazine);

            dal.Insert(issue);
            dal.Commit();

           
            Issue issueDAL = dal.GetAll<Issue>().First();
            Assert.IsNotNull(issueDAL,"Issue not properly stored and is null");
            Assert.AreEqual(issueDAL.Number, TestData.EXPECTED_ISSUE_NUMBER, "Issue number not properly stored.");
            Assert.AreEqual(magazine, issueDAL.Magazine, "Magazine not properly stored.");

            Assert.IsNotNull(issueDAL.PublishedPapers, "Collection of Papers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, issueDAL.PublishedPapers.Count, "Collection of Papers not properly initialized. \n The list should be empty\n");

        }

        [TestMethod]
        public void StoresDataWithRelations()
        {
            User chief = new User(TestData.EXPECTED_CHIEF_ID, TestData.EXPECTED_CHIEF_NAME, TestData.EXPECTED_CHIEF_SURNAME, TestData.EXPECTED_CHIEF_ALERTED, TestData.EXPECTED_CHIEF_AREASOFINTEREST, TestData.EXPECTED_CHIEF_EMAIL, TestData.EXPECTED_CHIEF_LOGIN, TestData.EXPECTED_CHIEF_PASSWORD);
            Magazine.Entities.Magazine magazine = new Magazine.Entities.Magazine(TestData.EXPECTED_MAGAZINE_NAME, chief);
            Issue issue = new Issue(TestData.EXPECTED_ISSUE_NUMBER, magazine);
            User editor = new User(TestData.EXPECTED_USER_ID, TestData.EXPECTED_USER_NAME, TestData.EXPECTED_USER_SURNAME, TestData.EXPECTED_USER_ALERTED, TestData.EXPECTED_USER_AREASOFINTEREST, TestData.EXPECTED_USER_EMAIL, TestData.EXPECTED_USER_LOGIN, TestData.EXPECTED_USER_PASSWORD);
            Area area = new Area(TestData.EXPECTED_AREA_NAME, editor, magazine);

            User user = new User(TestData.EXPECTED_USER2_ID, TestData.EXPECTED_USER2_NAME, TestData.EXPECTED_USER2_SURNAME, TestData.EXPECTED_USER2_ALERTED, TestData.EXPECTED_USER2_AREASOFINTEREST, TestData.EXPECTED_USER2_EMAIL, TestData.EXPECTED_USER2_LOGIN, TestData.EXPECTED_USER2_PASSWORD);
            Paper paper = new Paper(TestData.EXPECTED_PAPER_TITLE, TestData.EXPECTED_PAPER_UPLOADDATE, area, user);
            issue.PublishedPapers.Add(paper);
            dal.Insert(issue);
            dal.Commit();

            Issue issueDAL = dal.GetAll<Issue>().First();
            Assert.IsNotNull(issueDAL.PublishedPapers, "Collection of PublishedPapers not properly stored.");
            Assert.AreEqual(TestData.EXPECTED_ONE_ELEMENT_LIST_COUNT, issueDAL.PublishedPapers.Count, "Published paper not correctly stored in Issue");
            Assert.AreEqual(paper, issueDAL.PublishedPapers.FirstOrDefault(), "Published paper not correctly stored in Issue");
        }
    }
}
