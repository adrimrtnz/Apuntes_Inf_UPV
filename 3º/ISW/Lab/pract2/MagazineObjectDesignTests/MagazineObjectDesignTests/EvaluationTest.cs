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
    public class EvaluationTest
    {
        [TestMethod]
        public void VirtualPropertiesDefined()
        {
            
        }
        [TestMethod]
        public void NoParamsConstructorInitializesCollections()
        {
            
        }

        [TestMethod]
        public void ConstructorInitializesProps()
        {
            Evaluation eval = new Evaluation(TestData.EXPECTED_EVALUATION_ACCEPTED, TestData.EXPECTED_EVALUATION_COMMENTS, TestData.EXPECTED_EVALUATION_DATE);

            Assert.AreEqual(TestData.EXPECTED_EVALUATION_ACCEPTED, eval.Accepted, "Accepted not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_EVALUATION_COMMENTS, eval.Comments, "Comments not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
            Assert.AreEqual(TestData.EXPECTED_EVALUATION_DATE, eval.Date, "Date not properly initialized. Please check whether you have correctly assigned the parameters in the corresponding class.");
        }

    }
}
