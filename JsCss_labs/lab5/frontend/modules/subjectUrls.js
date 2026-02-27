class SubjectUrls {
    constructor() {
        this.baseUrl = 'http://localhost:3000';
    }

    getSubjects(title) {
        return `${this.baseUrl}/subjects?title=${title}`;
    }
}

export const subjectUrls = new SubjectUrls();
