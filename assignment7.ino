/* Διαβάστε τον κώδικα, προσπαθήστε να καταλάβετε τι κάνει από μόνοι σας (σκοπίμως δεν έχουν μπει σχόλια που να εξηγούν
  τι κάνουν οι διάφορες εντολές) και μετά γράψτε μόνοι σας το υπόλοιπο πρόγραμμα με τις οδηγίες που θα βρείτε στα σχόλια.
  Χρησιμοποιήστε της μεταβλητές αληθείας (boolean) ώστε οι εντολές της κάθε κατάστασης (state) να εκτελούνται μόνο μια φορά.
  Ο σκοπός σας είναι, να τελειώσετε το πρόγραμμα στο σπίτι και όταν το δοκιμάσετε στο αμαξάκι, το αμαξάκι να επιδείξει
  την εξής συμπεριφορά:
  Θα προχωρήσει περίπου 20 εκατοστά και θα στρίψει 180 μοίρες (αυτό είναι ήδη έτοιμο για εσάς).
  Θα προχωρήσει ΕΠΙΠΛΕΟΝ περίπου 60 εκατοστά (δηλαδή πόσα απ' την αρχή της λειτουργίας του;) και θα στρίψει 90 μοίρες προς
  τα αριστερά...
  Τέλος, θα συνεχίσει να κινείται ευθεία, μέχρι να διανύσει συνολικά (από την αρχή δηλαδή της λειτουργίας του) 150 εκατοστά. */
#include <Smartcar.h>

Odometer encoderLeft(190), encoderRight(190); //Βάλτε τους δικούς σας παλμούς ανά μέτρο
Gyroscope gyro(13); //Βάλτε την κατάλληλη τιμή σύμφωνα με το γυροσκόπιό σας
Car folkracer;
boolean state1Done = false;
boolean state2Done = false;

void setup() {
  gyro.attach(); // συνδεουμε το γυροσκοπιο
  encoderLeft.attach(3); //Χρησιμοποιήστε τα σωστά pins! Συνδεουμε το αριστερο encoder στο pin 3
  encoderRight.attach(2); // συνδεουμε το δεξι encoder στο pin 2
  encoderLeft.begin(); // Ξεκιναμε το αριστερο encoder
  encoderRight.begin(); // Ξεκιναμε το δεξι encoder
  gyro.begin(); // Ξεκιναει το γυροσκοπιο
  folkracer.begin(encoderLeft, encoderRight, gyro); // Το αυτοκινητο αρχιζει μαζι με τα δυο encoders και το gyro
  folkracer.enableCruiseControl();
  folkracer.setSpeed(0.5); //θέτουμε την ταχύτητα 0.5
}

void loop() {
  folkracer.updateMotors();
  unsigned long distance = encoderLeft.getDistance(); // η αποσταση γινεται η αποσταση που μετραει το encoder left
  distance = distance + encoderRight.getDistance(); // η αποσταση που εχει διανυσει ειναι η παλια αποσταση (αυτοι που μετραει απο το αριστερο encoder) συν την αποσταση που μετραει το δεξι encoder
  distance = distance / 2; // η αποσταση γινεται η αποσταση δια δυο
  if (distance > 20 && distance < 30) {
    if (state1Done == false) { // και εαν η πρωτη κατασταση δεν εχει πραγματοποιηθει
      folkracer.stop(); // Σταματάμε το αυτοκίνητο
      folkracer.rotate(175); // του λέμε να στρίψει 180 μοίρες
      folkracer.setSpeed(0.5); // βάζουμε ταχύτητα 0.5
      state1Done = true; // ηπ ρωτη κατασταση εχει ολοκληρωθει
    }
  }
  //TO-DO
  //Όταν το αυτοκινητάκι έχει διανύσει από 80 μέχρι 90 εκατοστά, τότε σταματήστε το και μετά περιστρέψτε το κατά 90 μοίρες
  //στα δεξιά. Στη συνέχεια, θέστε ταχύτητα 0.5 μέτρα το δευτερόλεπτο
  if (distance > 100 && distance < 140 && state2Done == false) {
     folkracer.stop(); // Σταματάμε το αυτοκίνητο
     folkracer.rotate(85); // του λέμε να στρίψει 90 μοίρες δεξιά
     folkracer.setSpeed(0.5); //βάζουμε ταχύτητα 0.5
     state2Done = true; // η δευτερη κατασταση εχει ολοκληρωθει
  }
  //TO-DO
  //Όταν το αυτοκινητάκι έχει διανύσει απόσταση μεγαλύτερη των 150 εκατοστών, τότε πείτε του να σταματήσει (ή εναλλακτικά θέστε
  //ταχύτητα μηδέν)
  if (distance > 300) { // εαν η αποσταση που εχει καλυψει ειναι μεγαλυτερη απο 150
    folkracer.stop(); // σταματαμε το αυτοκινητο
  }
}
