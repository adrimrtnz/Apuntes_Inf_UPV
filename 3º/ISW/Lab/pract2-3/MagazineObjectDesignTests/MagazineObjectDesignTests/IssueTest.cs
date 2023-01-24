using Magazine.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Reflection;

namespace MagazineObjectDesignTests
{
    [TestClass]
    public class IssueTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {

            PropertyInfo property = typeof(Issue).GetProperty("PublishedPapers");
            Assert.IsTrue(property.GetMethod.IsVirtual, "PublishedPapers property should be declared virtual.");

            property = typeof(Issue).GetProperty("Magazine");
            Assert.IsTrue(property.GetMethod.IsVirtual, "Magazine property should be declared virtual.");

        }
       

        [TestMethod]
        public void NoParamsConstructorInitializesCollections()
        {
            Issue issue = new Issue();
            Assert.AreNotSame(null, issue, "There must be a constructor without parameters.");
            Assert.IsNotNull(issue.PublishedPapers, "Collection of PublishedPapers not properly initialized. \n Patch the problem adding:  PublishedPapers = new List<Paper>();");
            Assert.AreEqual(TestData.EXPECTED_EMPTY_LIST_COUNT, issue.PublishedPapers.Count, "Collection of PublishedPapers not properly initialized. \n The list should be empty\n");
        }
         
        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Issue issue = new Issue(TestData.EXPECTED_ISSUE_NUMBER, TestData.EXPECTED_MAGAZINE);
            
            Assert.AreEqual(TestData.EXPECTED_ISSUE_NUMBER, issue.Number, "Number not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_MAGAZINE, issue.Magazine, "Magazine not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.IsNotNull(issue.PublishedPapers, "Collection of PublishedPapers not properly initialized. \n Patch the problem adding:  :this() to the constructor with parameters");

        }
    }
}
