// Capstone exercise sample -- combines everything from classes and access
// control through inheritance, virtual dispatch, abstract classes, and
// overloading in one program. See exercise.html for the full brief.
//
// Use case: RR Skillverse, a platform built to make learning accessible,
// interesting, and available to everyone -- tracking a learner's progress
// in a course, granting extra time when someone needs it, and issuing a
// certificate the moment a course is actually finished.
//
// Compile: g++ -std=c++17 12_rr_skillverse_course_tracker.cpp -o course_tracker
// Run:     course_tracker.exe   (Windows)   or   ./course_tracker   (Linux/macOS)
#include <iostream>
#include <string>
using namespace std;

// Every course format on RR Skillverse is a Course first (inheritance).
class Course {
protected:
    string learnerName;
    string courseTitle;
    int daysExtended = 0;

    // Static members: one shared, platform-wide dashboard for every course object.
    static int totalEnrollments;
    static int totalCertificatesIssued;

public:
    Course(const string& learner, const string& title)
        : learnerName(learner), courseTitle(title) {
        ++totalEnrollments;
        cout << "[enrolled] " << learnerName << " joined \"" << courseTitle << "\"\n";
    }

    // Virtual destructor: safe cleanup through a base pointer/reference.
    virtual ~Course() {
        --totalEnrollments;
        cout << "[exited] " << learnerName << " left \"" << courseTitle << "\"\n";
    }

    // Pure virtual functions: every concrete course must define its own contract (abstract class).
    virtual bool isComplete() const = 0;
    virtual string statusLine() const = 0;
    virtual double weeklyHours() const = 0;

    // Function overloading: two different ways to grant a learner extra time.
    void requestExtraTime(int days) {
        daysExtended += days;
    }
    void requestExtraTime(int days, const string& reason) {
        daysExtended += days;
        cout << "  " << learnerName << " granted " << days << " extra day(s): " << reason << "\n";
    }

    static int enrollmentCount() { return totalEnrollments; }
    static int certificatesIssued() { return totalCertificatesIssued; }

    // Friend function: certificate issuing needs direct access to protected learner/course data.
    friend void issueCertificateIfComplete(const Course& course);

    friend ostream& operator<<(ostream& out, const Course& course) {
        out << course.learnerName << " -> " << course.courseTitle
            << " [" << course.statusLine() << "]";
        return out;
    }

    // Operator overloading: combine two enrollments into one weekly study-hours estimate.
    friend double operator+(const Course& a, const Course& b) {
        return a.weeklyHours() + b.weeklyHours();
    }
};

int Course::totalEnrollments = 0;
int Course::totalCertificatesIssued = 0;

void issueCertificateIfComplete(const Course& course) {
    if (course.isComplete()) {
        ++Course::totalCertificatesIssued;
        cout << "  Certificate issued to " << course.learnerName
             << " for \"" << course.courseTitle << "\"\n";
    } else {
        cout << "  Not yet eligible for a certificate: " << course.learnerName << "\n";
    }
}

class VideoCourse : public Course {
    double percentWatched;
public:
    VideoCourse(const string& learner, const string& title, double percent)
        : Course(learner, title), percentWatched(percent) {}
    bool isComplete() const override { return percentWatched >= 90.0; }
    string statusLine() const override {
        return "self-paced video, " + to_string((int)percentWatched) + "% watched";
    }
    double weeklyHours() const override { return 2.5; }
};

class LiveWorkshop : public Course {
    int sessionsAttended;
    int totalSessions;
public:
    LiveWorkshop(const string& learner, const string& title, int attended, int total)
        : Course(learner, title), sessionsAttended(attended), totalSessions(total) {}
    bool isComplete() const override { return sessionsAttended >= totalSessions; }
    string statusLine() const override {
        return "live workshop, " + to_string(sessionsAttended) + "/" +
               to_string(totalSessions) + " sessions attended";
    }
    double weeklyHours() const override { return totalSessions * 1.5; } // 1.5 hrs per session
};

int main() {
    VideoCourse meera("Meera", "C++ Foundations", 92.0);
    LiveWorkshop dev("Dev", "C++ Mentorship Circle", 3, 4);

    cout << meera << "\n";
    cout << dev << "\n";

    dev.requestExtraTime(3, "exam week conflict"); // second overload

    cout << "Combined weekly study hours for Meera+Dev: " << (meera + dev) << "\n";

    issueCertificateIfComplete(meera);
    issueCertificateIfComplete(dev);

    cout << "Active enrollments: " << Course::enrollmentCount() << "\n";
    cout << "Certificates issued so far: " << Course::certificatesIssued() << "\n";
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  VideoCourse meera(...) constructs: Course's constructor runs
//         first (base-before-derived), totalEnrollments becomes 1, prints
//         "[enrolled] Meera joined "C++ Foundations"". percentWatched=92.0.
// STEP 2  LiveWorkshop dev(...) constructs similarly: totalEnrollments
//         becomes 2, prints "[enrolled] Dev joined "C++ Mentorship
//         Circle"". sessionsAttended=3, totalSessions=4.
// STEP 3  cout << meera calls the friend operator<<, which itself calls
//         meera.statusLine() (virtual -> VideoCourse's version) ->
//         prints "Meera -> C++ Foundations [self-paced video, 92%
//         watched]". cout << dev similarly prints "Dev -> C++ Mentorship
//         Circle [live workshop, 3/4 sessions attended]".
// STEP 4  dev.requestExtraTime(3, "exam week conflict") calls the
//         TWO-argument overload (matched because two arguments were
//         given): daysExtended becomes 3, prints "  Dev granted 3 extra
//         day(s): exam week conflict".
// STEP 5  meera + dev invokes the friend operator+: meera.weeklyHours()
//         (VideoCourse's override) returns 2.5; dev.weeklyHours()
//         (LiveWorkshop's override) returns totalSessions(4)*1.5 = 6.0.
//         Sum = 8.5. Prints "Combined weekly study hours for Meera+Dev:
//         8.5".
// STEP 6  issueCertificateIfComplete(meera): meera.isComplete() checks
//         percentWatched(92.0) >= 90.0 -> true -> totalCertificatesIssued
//         becomes 1, prints "  Certificate issued to Meera for "C++
//         Foundations"".
// STEP 7  issueCertificateIfComplete(dev): dev.isComplete() checks
//         sessionsAttended(3) >= totalSessions(4) -> false -> prints "
//         Not yet eligible for a certificate: Dev".
// STEP 8  "Active enrollments: 2" and "Certificates issued so far: 1"
//         print, reading the shared static counters.
// STEP 9  main() ends; meera and dev go out of scope, each running
//         Course's virtual destructor (base-class cleanup, since neither
//         subclass defines its own): totalEnrollments decrements twice,
//         printing "[exited] Meera left "C++ Foundations"" then "[exited]
//         Dev left "C++ Mentorship Circle"" (destruction order is the
//         REVERSE of construction order, so dev's destructor actually
//         runs before meera's).

